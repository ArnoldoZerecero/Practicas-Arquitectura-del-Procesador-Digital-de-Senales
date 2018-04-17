/*
 * main implementation: use this 'C' sample to create your own application
 *
 */

#include "derivative.h" /* include peripheral declarations */
#include "Correlacion.h"
#include "ADC.h"
#include "ButtonDriver.h"
#include "LedDriver.h"
#include "PIT.h"

#define LED_VERDE 2
#define LED_ROJO 1
#define BOTON_APRENDER_SENAL 0


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

int main(void)

{	vfnADCInit(&InitAdcParameters); /*Se inicializan los m�dulos*/
	vfnButtonInit(); 
	vfnLedInit();
	vfnPitInit(TARGET_TIME_100US,0); /*Inicializaci�n del PIT, sin interrupciones*/
	vfnPitStart(); /*Comienza el contador del PIT*/

	unsigned char baSenalEntrada[SIZE]; 
	unsigned char *pbSenalEntrada = &baSenalEntrada[0];
	unsigned char baSenalComparacion[SIZE];
	unsigned char *pbSenalComparacion = &baSenalComparacion[0];
	
	unsigned long *pdwCorrReturn = 0; /*Apuntador para almacenar la direcci�n de retorno de la funci�n de correlaci�n. Este apuntar� a todas las correlaciones hechas*/
	
	unsigned long dwEnergiaCorrelacion = 0;
	unsigned long dwEnergiaAutocorrelacion = 0;
	unsigned long dwDiferenciaEnergia = 0; /*Resultado de la diferencia de energ�a entre la autocorrelaci�n y la correlaci�n, para revisar qu� tan similares son*/
	
	unsigned short wCounter = SIZE; /*Contador para los ciclos de almacenar/comparar se�ales*/
	unsigned char flgComienzaMuestreo = 0; /*Se activa cuando se presiona el bot�n y el sistema aprende una se�al*/
	unsigned char flgSenalEncontrada = 0; /*Se activa cuando se hace el match y se debe encener el led*/

	for(;;) 
	{
		if(bfnButtonState(BOTON_APRENDER_SENAL)) /*Si se presiona el bot�n*/
		{
			vfnLedOff(LED_VERDE);
			vfnLedOn(LED_ROJO);  /*Se enciende el led rojo mientras se est� aprendiendo la se�al*/
			wCounter = SIZE; /*Se resetea el contador en N para el siguiente buffer desde el ADC*/
			flgSenalEncontrada = 0; /*Se apaga la bandera de se�al encontrada, debido a que se har� una nueva b�squeda con otra referencia*/

			while(wCounter--) /*Se almacenan SIZE elementos*/
			{
				while(PIT_CVAL0) /*Se espera a que termine la cuenta del PIT (100us)*/
				{
					/*Poll*/
				}
				*(pbSenalEntrada++) = wfnADCLectura(0); /*Se almacena lo que se ley� del ADC*/
			}
			pbSenalEntrada = &baSenalEntrada[0]; /*Se regresa el apuntador a su posici�n inicial*/
			
			pdwCorrReturn =  pdwfnCorrelacion(&baSenalEntrada[0],  &baSenalEntrada[SIZE - 1]); /*Se hace la autocorrelaci�n de la se�al aprendida*/
			dwEnergiaAutocorrelacion = *(pdwCorrReturn + SIZE - 1); /*La energ�a de la autocorrelaci�n es el valor a la mitad del buffer*/
			
			wCounter = SIZE; /*Se resetea el contador en N para el siguiente buffer desde el ADC*/
			flgComienzaMuestreo = 1;
			vfnLedOff(LED_ROJO);
		}
		
		if(flgComienzaMuestreo)
		{
			while(wCounter--) /*Se almacenan SIZE elementos*/
			{
				while(PIT_CVAL0) /*Se espera a que termine la cuenta del PIT (100us)*/
				{
					/*Poll*/
				}
				*(pbSenalComparacion++) = wfnADCLectura(0); /*Se almacena lo que se ley� del ADC*/
			}
			pbSenalComparacion = &baSenalComparacion[0]; /*Se regresa el apuntador a su posici�n inicial*/
			pdwCorrReturn =  pdwfnCorrelacion(&baSenalEntrada[0], &baSenalComparacion[SIZE - 1]); /*Se hace la correlaci�n de la se�al aprendida con la se�al le�da a comparar*/
			
			dwEnergiaCorrelacion = dwfnFindEnergy(pdwCorrReturn, SIZE*2 - 1); /*Se encuentra el valor m�s alto de la se�al*/

			/*Se hacen las restas para calcular las diferencias entre energ�as*/
			if(dwEnergiaAutocorrelacion > dwEnergiaCorrelacion)
			{
				dwDiferenciaEnergia = dwEnergiaAutocorrelacion - dwEnergiaCorrelacion;
			}
			else
			{
				dwDiferenciaEnergia = dwEnergiaCorrelacion - dwEnergiaAutocorrelacion;
			}
			
			if(dwDiferenciaEnergia < (dwEnergiaAutocorrelacion/15)) /*Rango de error*/
			{
				flgSenalEncontrada = 1;
			}
			else
			{
				flgSenalEncontrada = 0;
			}
			
			wCounter = SIZE; /*Se resetea el contador en N para el siguiente buffer desde el ADC*/
		}
		
		if(flgSenalEncontrada)
		{
			vfnLedOn(LED_VERDE);
		}
		else
		{
			vfnLedOff(LED_VERDE);
		}
	}

	return 0;
}

