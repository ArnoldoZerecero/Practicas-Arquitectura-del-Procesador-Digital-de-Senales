/*
 * main implementation: use this 'C' sample to create your own application
 *
 */

#include "derivative.h" /* include peripheral declarations */
#include "MultiplicacionMatrices.h"


int main(void)
{
	unsigned char *pResult = 0; /*Apuntador que recibirá la dirección de la matriz resultante de la función*/
	unsigned char baMatrizResultante[SIZE][SIZE]; /*Arreglo donde se guardará la matriz resultante en main*/
	unsigned char *pMatrizResultante = &baMatrizResultante[0][0]; /*Apuntador a la matriz resultante*/
	unsigned char bResultCounter = SIZE*SIZE; /*Contador para ir guardando cada valor de la matriz resultante*/
	
	const unsigned char kbaMatrizA[SIZE][SIZE] = 
	{
			{1,2,3,4,5},
			{1,2,3,4,5},
			{1,2,3,4,5},
			{1,2,3,4,5},
			{1,2,3,4,5}
	};  
	
	const unsigned char kbaMatrizB[SIZE][SIZE] = 
	{
			{1,2,3,4,5},
			{1,2,3,4,5},
			{1,2,3,4,5},
			{1,2,3,4,5},
			{1,2,3,4,5}
	};  

	pResult = bpfnMultiplicacionMatrices(&kbaMatrizA[0][0], &kbaMatrizB[0][0]);
	
	while(bResultCounter--) /*Utilizando el apuntador, se almacena cada dato de la matriz resultante de la función en una nueva de main*/
	{
		*pMatrizResultante= *pResult;
		pResult++;
		pMatrizResultante++;
	}
	return 0;
}
