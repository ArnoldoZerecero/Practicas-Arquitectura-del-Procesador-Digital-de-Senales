/*
 * MultplicacionMatrices.c
 *
 *  Created on: Jan 16, 2018
 *      Author: Jes�s Arnoldo Zerecero N��ez
 */

#include "MultiplicacionMatrices.h"

	
unsigned char * bpfnMultiplicacionMatrices(const unsigned char * pMatrizA, const unsigned char * pMatrizB)
{
	static unsigned char _baMatrizResultante[SIZE][SIZE]; /*Aqu� se almacenar� la matriz resultante*/
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
				if(bCounterProductos > 0) /*Para evitar realizar un incremento dem�s, se utiliza esta condici�n*/
				{
					pMatrizA++; /*El apuntador de A se mover� a trav�s del rengl�n*/
					pMatrizB += SIZE; /*El apuntador de B se mover� a trav�s de la columna*/
				}
			}
			pMatrizR++; /*La siguiente suma de productos se almacenar� en la siguiente posici�n de la matriz resultante*/
			pMatrizA -= SIZE - 1; /*Se reinicia el apuntador de A*/
			pMatrizB -= SIZE*(SIZE - 1) - 1; /*Se reinicia el apuntador de B y se le agrega 1 al mismo*/
			bCounterProductos = SIZE; /*Se reinicia el contador*/
		}
		bCounterInstancias = SIZE; /*Se reinicia el contador*/
		pMatrizA += SIZE; /*Ahora el contador de A se mover� una columna*/
		pMatrizB -= SIZE; /*Ahora el contador de B se debe reiniciar hasta su posici�n inicial (1,1)*/
	}

	return (unsigned char *)_baMatrizResultante; /*Se regresa un apuntador a la matriz resultante*/
}
