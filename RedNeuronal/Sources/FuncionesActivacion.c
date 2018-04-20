/*
 * FuncionesActivacion.c
 *
 *  Created on: Apr 11, 2018
 *      Author: Jesús Arnoldo Zerecero Núñez
 */
#include "FuncionesActivacion.h"

unsigned long (* const vfnapFunciones[])(unsigned long) = /*Arreglo de apuntadores a las funciones*/
{
		dwfnBypass,
		dwfnLogSig,
		dwfnPurelin
};

unsigned long dwfnBypass(unsigned long dwInputData)
{
	return dwInputData;
}

unsigned long dwfnLogSig(unsigned long dwInputData)
{
	return dwInputData;
}

unsigned long dwfnPurelin(unsigned long dwInputData)
{
	return dwInputData;
}


