/*
 * Convolucion.c
 *
 *  Created on: Feb 18, 2018
 *      Author: Jesús Arnoldo Zerecero Núñez
 */

#include "Convolucion.h"

unsigned long dwfnConvolucion (const unsigned char * pbBufferSistema, unsigned char * pbBufferEntrada, unsigned char bSize, unsigned char bInputNumber)
{
	unsigned char bCounter = bSize - 1; /*Contador para el ciclo*/
	unsigned long dwResultado = 0; /*Variable de retorno*/

	while (bCounter--) 
	{
		*pbBufferEntrada = *(pbBufferEntrada - 1); /*Se recorre el buffer, eliminando el dato más antiguo*/
		dwResultado = (unsigned short)(((unsigned short)*pbBufferSistema--)*((unsigned short)*pbBufferEntrada--)) + dwResultado; /*Se hacen SIZE-1 sumas de productos*/
	}
	*pbBufferEntrada = bInputNumber; /*El argumento de entrada se acomoda en la primera posición del buffer*/ 
	dwResultado = (unsigned short)(((unsigned short)*pbBufferSistema)*((unsigned short)*pbBufferEntrada)) + dwResultado; /*Se hace la última multiplicación*/

	return dwResultado;
}
