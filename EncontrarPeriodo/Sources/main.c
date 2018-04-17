/*
 * main implementation: use this 'C' sample to create your own application
 *
 */

#include "derivative.h" /* include peripheral declarations */
#include "Correlacion.h"
#include "ADC.h"
#include "PIT.h"
#include "UART.h"
#include "MISCELANEO.h"

ADCConfigInit_t InitAdcParameters = /*Inicializamos los valores de la estructura*/
{
		0, /*Se utilizar� bus clk*/ 
		0, /*Tiempo de muestreo corto*/
		0, /*Resoluci�n de 8 bits*/
		0, /*Este par�metro se desprecia debido a que ser�n muestreos cortos*/
		1, /*Conversi�n de alta velocidad*/
		0, /*Este par�metro se desprecia debido a que no se promedian muestras por hardware*/
		0, /*Promediado por hardware desactivado*/
		0, /*Este par�metro se desprecia debido a que no se promedian muestras por hardware*/
		OFFSET, /*Offset*/
};

UartConfigInit_t InitUartParameters = /*Inicializamos los valores de la estructura*/
{
		0, /*Solo 1 stop bit*/
		BAUD_RATE, /*84*/
		0, /*0 = 8 bits de longitud, 1 = 9 bits de longitud*/ 
		0, /*0 = paridad desactivada, 1 = paridad activada*/
		0, /*0 = paridad par, 1 = paridad impar*/
		OSR, /*25*/
		0 /*Sin callback*/
};

int main(void)
{
	unsigned char baSenalEntrada[SIZE]; 
	unsigned char *pbSenalEntrada = &baSenalEntrada[0];
	
	unsigned long *pdwCorrReturn = 0; /*Apuntador para almacenar la direcci�n de retorno de la funci�n de correlaci�n. Este apuntar� a todas las correlaciones hechas*/
	
	unsigned short wPeriodoCorrelacion = 0;
	unsigned char baBufferPeriodo[4]; /*Arreglo donde se almacenar�n los d�gitos del periodo para ser mandados por UART*/
	unsigned char *pbBufferPeriodo = &baBufferPeriodo[0];
	
	unsigned short wCounter = SIZE; /*Contador para llenar el buffer desde el ADC*/
	
	vfnADCInit(&InitAdcParameters); /*Inicializaci�n del ADC*/
	vfnUartInit(&InitUartParameters); /*Inicializaci�n del UART*/
	vfnPitInit(TARGET_TIME_100US,0); /*Inicializaci�n del PIT, sin interrupciones*/
	vfnPitStart(); /*Comienza el contador del PIT*/
		
	for(;;)
	{
		while(wCounter--) /*Se almacenan 2000 elementos*/
		{
			while(PIT_CVAL0) /*Se espera a que termine la cuenta del PIT (100us)*/
			{
				/*Poll*/
			}
			*(pbSenalEntrada++) = wfnADCLectura(0); /*Se almacena lo que se ley� del ADC*/
		}
		pbSenalEntrada = &baSenalEntrada[0];
		wCounter = SIZE;
		pdwCorrReturn =  pdwfnCorrelacion(&baSenalEntrada[0],  &baSenalEntrada[SIZE - 1]); /*Se hace la autocorrelaci�n de la se�al*/
		wPeriodoCorrelacion = wfnFindPeriod(pdwCorrReturn, SIZE*2 - 1); /*Se calcula el periodo*/

		wPeriodoCorrelacion = wPeriodoCorrelacion/2; /*Se ajusta el periodo para tenerlo en ms*/
		/*Se convierte el resultado a caracteres para ser mandado como una cadena*/
		wPeriodoCorrelacion = dwfnBCD(wPeriodoCorrelacion); 
		*pbBufferPeriodo++ = CLEAR_ALL_BUT_THOUSANDS(wPeriodoCorrelacion) + 48;
		*pbBufferPeriodo++ = CLEAR_ALL_BUT_HUNDREDS(wPeriodoCorrelacion) + 48;
		*pbBufferPeriodo++ = CLEAR_ALL_BUT_TENS(wPeriodoCorrelacion) + 48;
		*pbBufferPeriodo = CLEAR_ALL_BUT_UNITS(wPeriodoCorrelacion) + 48;
		
		pbBufferPeriodo = &baBufferPeriodo[0];
		vfnUartTransmision((unsigned char *)&baBufferPeriodo[0], sizeof(baBufferPeriodo));
	}
	return 0;
}
