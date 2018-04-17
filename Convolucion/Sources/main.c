/*
 * main implementation: use this 'C' sample to create your own application
 *
 */

#include "derivative.h" /* include peripheral declarations */
#include "UART.h"
#include "Convolucion.h"
#include "MISCELANEO.h"

UartConfigInit_t InitUartParameters = /*Inicializamos los valores de la estructura*/
{
		0, /*Solo 1 stop bit*/
		BAUD_RATE, /*84*/
		0, /*0 = 8 bits de longitud, 1 = 9 bits de longitud*/ 
		0, /*0 = paridad desactivada, 1 = paridad activada*/
		0, /*0 = paridad par, 1 = paridad impar*/
		OSR, /*25*/
		&vfnUARTCallback /*Apuntador a función Callback*/
};

volatile unsigned char gflgCharacterReceived = 0; /*Índice para cuando se tecleó algo en la terminal*/

volatile unsigned char gbNewCharacterReceived = 0; /*Variable para guardar el caracter tecleado en la terminal*/

const unsigned char kbBufferSistema[] = {5,6,7,8}; 

const unsigned char kbSize = sizeof(kbBufferSistema);

static unsigned char _bBufferEntrada[sizeof(kbBufferSistema)] = {0}; 

int main(void)
{
	unsigned long dwResultado = 0; /*Resultado de convolución*/
	unsigned char baBufferResultado[6]; /*Buffer para almacenar los dígitos del resultado*/
	unsigned char *pbBufferResultado = &baBufferResultado[0];
	vfnUartInit(&InitUartParameters); /*Inicialización del UART*/

	for(;;) 
	{
		if(gflgCharacterReceived) /*Si se recibió un número para la convolución*/
		{
			gflgCharacterReceived = 0; /*Se reinicia bandera*/
			dwResultado = dwfnConvolucion(&kbBufferSistema[kbSize - 1], &_bBufferEntrada[kbSize - 1], kbSize, gbNewCharacterReceived);

			/*Se convierte el resultado a caracteres para ser mandado como una cadena*/
			dwResultado = dwfnBCD(dwResultado); 
			*pbBufferResultado++ = CLEAR_ALL_BUT_HUNDREDTHOUSANDS(dwResultado) + 48; 
			*pbBufferResultado++ = CLEAR_ALL_BUT_TENTHOUSANDS(dwResultado) + 48; 
			*pbBufferResultado++ = CLEAR_ALL_BUT_THOUSANDS(dwResultado) + 48;
			*pbBufferResultado++ = CLEAR_ALL_BUT_HUNDREDS(dwResultado) + 48;
			*pbBufferResultado++ = CLEAR_ALL_BUT_TENS(dwResultado) + 48;
			*pbBufferResultado = CLEAR_ALL_BUT_UNITS(dwResultado) + 48;
			pbBufferResultado = &baBufferResultado[0]; /*Se resetea el apuntador al comienzo del buffer*/
			
			vfnUartTransmision((unsigned char *)&baBufferResultado[0], sizeof(baBufferResultado));
		}
	}

	return 0;
}

void vfnUARTCallback(unsigned char bDatosReceptor)
{
	gbNewCharacterReceived = bDatosReceptor;
	gflgCharacterReceived = 1;
}

