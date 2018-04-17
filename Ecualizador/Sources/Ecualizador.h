/*
 * Ecualizador.h
 *
 *  Created on: Jan 21, 2018
 *      Author: Jesús Arnoldo Zerecero Núñez
 */

#ifndef ECUALIZADOR_H_
#define ECUALIZADOR_H_

#define MAX_POT_VALUE 5300 

void vfnEco(unsigned short wValorLeido, unsigned short wBufferSize);

void vfnDistorsion(unsigned short wValorLeido, unsigned short wValorPot);

void vfnVibrato(unsigned short wValorLeido, unsigned short wFactorFrecuencia);

void vfnInvertido(unsigned short wValorLeido);

#endif /* ECUALIZADOR_H_ */
