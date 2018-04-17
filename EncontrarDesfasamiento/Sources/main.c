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
		0, /*Se utilizará bus clk*/ 
		0, /*Tiempo de muestreo corto*/
		0, /*Resolución de 8 bits*/
		0, /*Este parámetro se desprecia debido a que serán muestreos cortos*/
		1, /*Conversión de alta velocidad*/
		0, /*Este parámetro se desprecia debido a que no se promedian muestras por hardware*/
		0, /*Promediado por hardware desactivado*/
		0, /*Este parámetro se desprecia debido a que no se promedian muestras por hardware*/
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
	unsigned char baSenalComparacion[SIZE];
	unsigned char *pbSenalComparacion = &baSenalComparacion[0];

	unsigned long *pdwCorrReturn = 0; /*Apuntador para almacenar la dirección de retorno de la función de correlación. Este apuntará a todas las correlaciones hechas*/

	unsigned short wCounter = SIZE; /*Contador para llenar el buffer desde el ADC*/

	/*Variables para el cálculo del desfase*/
	unsigned short wAutocorrelationPeakLocation = 0;
	unsigned short wCorrelationPeakLocation = 0;
	unsigned short wDesfase = 0;
	
	unsigned char baBufferDesfase[4]; /*Arreglo donde se almacenarán los dígitos del periodo para ser mandados por UART*/
	unsigned char *pbBufferDesfase= &baBufferDesfase[0];
	
	vfnADCInit(&InitAdcParameters); /*Inicialización del ADC*/
	vfnUartInit(&InitUartParameters); /*Inicialización del UART*/
	vfnPitInit(TARGET_TIME_100US,0); /*Inicialización del PIT, sin interrupciones*/
	vfnPitStart(); /*Comienza el contador del PIT*/

	for(;;)
	{
		while(wCounter--) /*Se almacenan SIZE elementos*/
		{

			*(pbSenalEntrada++) = wfnADCLectura(0); /*Se almacena lo que se leyó del ADC*/
			*(pbSenalComparacion++) = wfnADCLectura(3); /*Se almacena lo que se leyó del ADC*/
		}	
		wCounter = SIZE; /*Se reinicia el contador para llenar el siguiente buffer desde el ADC*/
		pbSenalEntrada = &baSenalEntrada[0]; /*Se reinician los apuntadores*/
		pbSenalComparacion = &baSenalComparacion[0];

		pdwCorrReturn =  pdwfnCorrelacion(&baSenalEntrada[0],  &baSenalComparacion[SIZE - 1]); /*Se hace la autocorrelación de la señal aprendida*/

		wAutocorrelationPeakLocation = SIZE - 1; /*El valor máximo de la autocorrelación es el valor a la mitad del buffer*/
		wCorrelationPeakLocation = wfnFindMaxPeakLocation(pdwCorrReturn, SIZE*2 - 1); /*Se busca en qué elemento está el valor máximo*/

		if(wAutocorrelationPeakLocation > wCorrelationPeakLocation) /*El desfasamiento es igual a la diferencia entre los máximos globales de las señales*/
		{
			wDesfase = wAutocorrelationPeakLocation - wCorrelationPeakLocation;
		}
		else
		{
			wDesfase = wCorrelationPeakLocation - wAutocorrelationPeakLocation;
		}
		
		/*Se convierte el resultado a caracteres para ser mandado como una cadena*/
		wDesfase = dwfnBCD(wDesfase); 
		*pbBufferDesfase++ = CLEAR_ALL_BUT_THOUSANDS(wDesfase) + 48;
		*pbBufferDesfase++ = CLEAR_ALL_BUT_HUNDREDS(wDesfase) + 48;
		*pbBufferDesfase++ = CLEAR_ALL_BUT_TENS(wDesfase) + 48;
		*pbBufferDesfase = CLEAR_ALL_BUT_UNITS(wDesfase) + 48;
		
		pbBufferDesfase = &baBufferDesfase[0];
		vfnUartTransmision((unsigned char *)&baBufferDesfase[0], sizeof(baBufferDesfase));
	}
	
	return 0;
}
