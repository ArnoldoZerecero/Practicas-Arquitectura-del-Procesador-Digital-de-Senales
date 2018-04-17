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

int main(void)

{	vfnADCInit(&InitAdcParameters); /*Se inicializan los módulos*/
	vfnButtonInit(); 
	vfnLedInit();
	vfnPitInit(TARGET_TIME_100US,0); /*Inicialización del PIT, sin interrupciones*/
	vfnPitStart(); /*Comienza el contador del PIT*/

	unsigned char baSenalEntrada[SIZE]; 
	unsigned char *pbSenalEntrada = &baSenalEntrada[0];
	unsigned char baSenalComparacion[SIZE];
	unsigned char *pbSenalComparacion = &baSenalComparacion[0];
	
	unsigned long *pdwCorrReturn = 0; /*Apuntador para almacenar la dirección de retorno de la función de correlación. Este apuntará a todas las correlaciones hechas*/
	
	unsigned long dwEnergiaCorrelacion = 0;
	unsigned long dwEnergiaAutocorrelacion = 0;
	unsigned long dwDiferenciaEnergia = 0; /*Resultado de la diferencia de energía entre la autocorrelación y la correlación, para revisar qué tan similares son*/
	
	unsigned short wCounter = SIZE; /*Contador para los ciclos de almacenar/comparar señales*/
	unsigned char flgComienzaMuestreo = 0; /*Se activa cuando se presiona el botón y el sistema aprende una señal*/
	unsigned char flgSenalEncontrada = 0; /*Se activa cuando se hace el match y se debe encener el led*/

	for(;;) 
	{
		if(bfnButtonState(BOTON_APRENDER_SENAL)) /*Si se presiona el botón*/
		{
			vfnLedOff(LED_VERDE);
			vfnLedOn(LED_ROJO);  /*Se enciende el led rojo mientras se esté aprendiendo la señal*/
			wCounter = SIZE; /*Se resetea el contador en N para el siguiente buffer desde el ADC*/
			flgSenalEncontrada = 0; /*Se apaga la bandera de señal encontrada, debido a que se hará una nueva búsqueda con otra referencia*/

			while(wCounter--) /*Se almacenan SIZE elementos*/
			{
				while(PIT_CVAL0) /*Se espera a que termine la cuenta del PIT (100us)*/
				{
					/*Poll*/
				}
				*(pbSenalEntrada++) = wfnADCLectura(0); /*Se almacena lo que se leyó del ADC*/
			}
			pbSenalEntrada = &baSenalEntrada[0]; /*Se regresa el apuntador a su posición inicial*/
			
			pdwCorrReturn =  pdwfnCorrelacion(&baSenalEntrada[0],  &baSenalEntrada[SIZE - 1]); /*Se hace la autocorrelación de la señal aprendida*/
			dwEnergiaAutocorrelacion = *(pdwCorrReturn + SIZE - 1); /*La energía de la autocorrelación es el valor a la mitad del buffer*/
			
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
				*(pbSenalComparacion++) = wfnADCLectura(0); /*Se almacena lo que se leyó del ADC*/
			}
			pbSenalComparacion = &baSenalComparacion[0]; /*Se regresa el apuntador a su posición inicial*/
			pdwCorrReturn =  pdwfnCorrelacion(&baSenalEntrada[0], &baSenalComparacion[SIZE - 1]); /*Se hace la correlación de la señal aprendida con la señal leída a comparar*/
			
			dwEnergiaCorrelacion = dwfnFindEnergy(pdwCorrReturn, SIZE*2 - 1); /*Se encuentra el valor más alto de la señal*/

			/*Se hacen las restas para calcular las diferencias entre energías*/
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

