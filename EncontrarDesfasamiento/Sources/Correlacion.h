/*
 * Correlacion.h
 *
 *  Created on: Mar 4, 2018
 *      Author: Jesús Arnoldo Zerecero Núñez
 */

#ifndef CORRELACION_H_
#define CORRELACION_H_

#define SIZE 1000

unsigned long * pdwfnCorrelacion(unsigned char * pbBufferSistema, unsigned char * pbBufferEntrada);

unsigned long dwfnFindEnergy(unsigned long * pdwCorrelacion, unsigned short wSize);

unsigned short wfnFindPeriod(unsigned long * pdwCorrelacion, unsigned short wSize);

unsigned short wfnFindMaxPeakLocation(unsigned long * pdwCorrelacion, unsigned short wSize);

#endif /* CORRELACION_H_ */
