#include "ADC.h"
#include "DAC.h"
#include "UART0.h"

#define TRANSMITIR_RECIBIR 0 /*0 para transmitir (filtros analógicos), 1 para recibir (filtros digitales)*/
#define MUESTRAS 500000

int main(void)

{  
	vfnADCInit(); /*Inicialización de módulos*/
	vfndac_Init();
	UART_vfnInitialization();

	unsigned long dwCounter = MUESTRAS; /*Contador para el ciclo (mandar o recibir N muestras*/
	unsigned char bInput = 0; /*Variable de retorno del ADC*/

	for(;;) 
	{	
		while(dwCounter--)
		{
			bInput = bfnADCLectura(0); /*Se lee el ADC*/
#if TRANSMITIR_RECIBIR == 0
			vfndac_Output(bInput); /*Se manda al DAC*/
#endif
			UART_vfnTransmitBuffer(bInput); /*Se manda por UART a Matlab*/
		}
		dwCounter = MUESTRAS;

#if TRANSMITIR_RECIBIR == 1  	
		while(dwCounter--)
		{
			UART_bfnReceiveBuffer(); /*Se manda al DAC lo que se recibió por UART desde Matlab*/
		}
		dwCounter = MUESTRAS;
#endif
	}
	return 0;
}
