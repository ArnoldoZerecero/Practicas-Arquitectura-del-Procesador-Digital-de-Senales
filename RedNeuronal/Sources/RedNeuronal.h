/*
 * RedNeuronal.h
 *
 *  Created on: Apr 11, 2018
 *      Author: Jesús Arnoldo Zerecero Núñez
 */

#ifndef REDNEURONAL_H_
#define REDNEURONAL_H_

typedef struct /*Variables de estado*/
{
	const unsigned char kbIndexFuncion;
	const unsigned long * kpdwInputs;
	const unsigned short * kpwPesos;
	unsigned long * pdwResultArray;
}EntradasNeurona_t;

void vfnNeurona(EntradasNeurona_t *psNeuronas);

#endif /* REDNEURONAL_H_ */
