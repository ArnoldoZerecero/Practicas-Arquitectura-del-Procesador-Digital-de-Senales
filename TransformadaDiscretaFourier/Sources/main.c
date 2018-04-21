/*
 * main implementation: use this 'C' sample to create your own application
 *
 */

#include "derivative.h" /* include peripheral declarations */
#include "DFT.h"
#include "ADC.h"
#include "PIT.h"

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
{
	unsigned char baSenalEntrada[SIZE] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	unsigned char *pbSenalEntrada = &baSenalEntrada[0];
	signed long dbaDFTResult[SIZE]; /*Arreglo donde se almacenará en main el resultado de la DFT*/
	signed long *pdbDFTResult = &dbaDFTResult[0];
	signed long *pdbReturnValue = 0; /*Apuntador para almacenar la dirección del arreglo de retorno*/
	unsigned short wCounter = SIZE; /*Contador para llenar los buffers*/
	
	vfnADCInit(&InitAdcParameters); /*Inicialización del ADC*/
	vfnPitInit(TARGET_TIME_100US,0); /*Inicialización del PIT, sin interrupciones*/
	vfnPitStart(); /*Comienza el contador del PIT*/
	for(;;) 
	{	
	//	while(wCounter--) /*Se almacenan 128 elementos*/
		//{
			//while(PIT_CVAL0) /*Se espera a que termine la cuenta del PIT (100us)*/
			//{
				/*Poll*/
			//}
			//*(pbSenalEntrada++) = wfnADCLectura(0); /*Se almacena lo que se leyó del ADC*/
		//}
		//pbSenalEntrada = &baSenalEntrada[0];
		//wCounter = SIZE;

		pdbReturnValue = dbfnDFT(&baSenalEntrada[0], SIZE);
				
		while(wCounter--) /*Se llena el arreglo en main utilizando el arreglo de retorno*/
		{
			*(pdbDFTResult++) = *(pdbReturnValue++);
		}
		wCounter = SIZE;
		pdbReturnValue = 0; /*Se reinician las direcciones de los arreglos*/
		pdbDFTResult = &dbaDFTResult[0];
	}
	
	return 0;
}
