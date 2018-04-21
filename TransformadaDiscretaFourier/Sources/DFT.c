/*
 * DFT.c
 *
 *  Created on: Mar 11, 2018
 *      Author: Jesús Arnoldo Zerecero Núñez
 */
#include "DFT.h"
#include "SinCosTable.h"
#include "SinCosAngle.h"

signed long * dbfnDFT(unsigned char * pbBufferEntrada, const unsigned short kwSize)
{
	const unsigned short kwSizeSinTable = sizeof(kaSinTable)*2 - 1; /*Tamaño de la tabla de valores senoidales (4N - 1)*/
	unsigned short wCounter = kwSize; /*Contador para las sumas de productos (ciclo interno)*/
	unsigned short wCounterBufferFill = kwSize; /*Contador para el llenado del arreglo resultante (ciclo externo)*/
	unsigned short wSinTableIndex = 0; /*Índice para elegir el valor del angulo desde las funciones de angulo*/
	unsigned short wFrequencyFactor = kwSize - 1; /*Variable que indica de cuanto en cuanto se estarán barriendo los valores de la tabla de seno (N - 1 hasta 0)*/
	signed long dbResSin = 0; /*Acumulador de la multipicación con seno*/
	signed long dbResCos = 0; /*Acumulador de la multipicación con coseno*/
	static signed long _dbaBufferRes[SIZE]; /*Buffer resultante*/
	signed long *pdbBufferRes = &_dbaBufferRes[0];

	while(wCounterBufferFill--)
	{
		while(wCounter--)
		{
			while(wSinTableIndex > kwSizeSinTable) /*Si al barrer la tabla se sale de esta, se decrementa el índice a una posición válida equivalente a por cuánto se sobrepasó el tamaño de la tabla*/
			{
				wSinTableIndex -= kwSizeSinTable;
			}
			dbResSin += (*(pbBufferEntrada))*ifnSinValue(wSinTableIndex);
			dbResCos += (*(pbBufferEntrada++))*ifnCosValue(wSinTableIndex);
			wSinTableIndex += wFrequencyFactor; /*Se incrementa el índice según el factor de frecuencia actual*/
		}
		*(pdbBufferRes++) = dbResCos - dbResSin; 
		wFrequencyFactor--;
		wCounter = kwSize; /*Se reinician apuntadores y variables*/
		dbResSin = 0;
		dbResCos = 0;
		pbBufferEntrada -= kwSize;
		wSinTableIndex = 0;
	}
	return _dbaBufferRes;
}

unsigned char * bfnInvDFT (signed long * dbDFTRes, const unsigned short kwSize)
{
	
}
