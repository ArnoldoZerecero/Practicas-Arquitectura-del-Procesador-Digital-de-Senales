/*
 * DFT.h
 *
 *  Created on: Mar 11, 2018
 *      Author: Jesús Arnoldo Zerecero Núñez
 */

#ifndef DFT_H_
#define DFT_H_

#define SIZE 128

signed long * dbfnDFT(unsigned char * pbBufferEntrada, const unsigned short kwSize);

unsigned char * bfnInvDFT (signed long * dbDFTRes, const unsigned short kwSize);

#endif /* DFT_H_ */
