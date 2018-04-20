/*
 * FuncionesActivacion.h
 *
 *  Created on: Apr 11, 2018
 *      Author: Jesús Arnoldo Zerecero Núñez
 */

#ifndef FUNCIONESACTIVACION_H_
#define FUNCIONESACTIVACION_H_

#define SIZE 3
#define BYPASS 0
#define LOGSIG 1
#define PURELIN 2


extern unsigned long (* const vfnapFunciones[SIZE])(unsigned long);

unsigned long dwfnBypass(unsigned long dwInputData);

unsigned long dwfnLogSig(unsigned long dwInputData);

unsigned long dwfnPurelin(unsigned long dwInputData);


#endif /* FUNCIONESACTIVACION_H_ */
