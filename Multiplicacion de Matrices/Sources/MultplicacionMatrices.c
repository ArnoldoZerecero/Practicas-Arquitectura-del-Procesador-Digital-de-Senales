/*
 * MultplicacionMatrices.c
 *
 *  Created on: Jan 16, 2018
 *      Author: Jesús Arnoldo Zerecero Núñez
 */

#include "MultiplicacionMatrices.h"

	
unsigned char * bpfnMultiplicacionMatrices(const unsigned char * pMatrizA, const unsigned char * pMatrizB)
{
	static unsigned char _baMatrizResultante[SIZE][SIZE]; /*Aquí se almacenará la matriz resultante*/
	unsigned char *pMatrizR = &_baMatrizResultante[0][0]; /*Apuntador para la matriz resultante*/
	unsigned char bCounter = SIZE; /*Se crean 3 contadores para los 3 ciclos*/
	unsigned char bCounterProductos = SIZE;
	unsigned char bCounterInstancias = SIZE;

	while(bCounter--)
	{
		while(bCounterInstancias--)
		{
			while(bCounterProductos--)
			{
				*pMatrizR += (*pMatrizA)*(*pMatrizB); /*Se va acumulando el resultado de SIZE sumas de productos en la matriz resultante*/
				if(bCounterProductos > 0) /*Para evitar realizar un incremento demás, se utiliza esta condición*/
				{
					pMatrizA++; /*El apuntador de A se moverá a través del renglón*/
					pMatrizB += SIZE; /*El apuntador de B se moverá a través de la columna*/
				}
			}
			pMatrizR++; /*La siguiente suma de productos se almacenará en la siguiente posición de la matriz resultante*/
			pMatrizA -= SIZE - 1; /*Se reinicia el apuntador de A*/
			pMatrizB -= SIZE*(SIZE - 1) - 1; /*Se reinicia el apuntador de B y se le agrega 1 al mismo*/
			bCounterProductos = SIZE; /*Se reinicia el contador*/
		}
		bCounterInstancias = SIZE; /*Se reinicia el contador*/
		pMatrizA += SIZE; /*Ahora el contador de A se moverá una columna*/
		pMatrizB -= SIZE; /*Ahora el contador de B se debe reiniciar hasta su posición inicial (1,1)*/
	}

	return (unsigned char *)_baMatrizResultante; /*Se regresa un apuntador a la matriz resultante*/
}
