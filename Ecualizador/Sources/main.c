/*
 * main implementation: use this 'C' sample to create your own application
 *
 */


#include "derivative.h" /* include peripheral declarations */
#include "PIT.h"
#include "DAC.h"
#include "ADC.h"
#include "Ecualizador.h"

#define EFECTO 0

ADCConfigInit_t InitAdcParameters = /*Inicializamos los valores de la estructura*/
{
		0, /*Se utilizará bus clk*/ 
		0, /*Tiempo de muestreo corto*/
		1, /*Resolución de 12 bits*/
		0, /*Este parámetro se desprecia debido a que serán muestreos cortos*/
		1, /*Conversión de alta velocidad*/
		0, /*Este parámetro se desprecia debido a que no se promedian muestras por hardware*/
		0, /*Promediado por hardware desactivado*/
		0, /*Este parámetro se desprecia debido a que no se promedian muestras por hardware*/
		OFFSET, /*Offset*/
};


int main(void)
{
	static unsigned short _wValorLeido = 0; /*Variable para almacenar el valor leido del ADC*/
	static unsigned short _wValorPot = 0; /*Variable para leer el valor leido del potenciómetro*/
	
	vfnADCInit(&InitAdcParameters); /*Inicialización del ADC*/
	vfnDACGPIOInit(); /*Inicialización del DAC*/
	vfnDACInitConfig();
	vfnPitInit(TARGET_TIME_100US,0); /*Inicialización del PIT, sin interrupciones*/
	vfnPitStart(); /*Comienza el contador del PIT*/
	
	for(;;) 
	{	   
		_wValorLeido = wfnADCLectura(0); /*Se obtiene el resultado de una conversión ADC, desde el canal DADP0*/
		_wValorPot = (wfnADCLectura(3)*330/256); /*Se adquiere el valor del pot desde el ADC (canal DADP3) y se convierte a unidades de voltaje*/
		while(PIT_CVAL0) /*Se espera a que termine la cuenta del PIT (100us)*/
		{
			/*Poll*/
		}
		if(EFECTO == 1)
		{
			vfnEco(_wValorLeido, _wValorPot);
		}
		else if(EFECTO == 2)
		{
			vfnDistorsion(_wValorLeido, _wValorPot);
		}
		else if(EFECTO == 3)
		{
			vfnVibrato(_wValorLeido, _wValorPot);
		}
		else if(EFECTO == 4)
		{
			vfnInvertido(_wValorLeido);
		}
		else /*Sin efecto*/
		{
			vfnDACWrite(_wValorLeido);
		}
	}
	
	return 0;
}
