/*
 * SinCosAngle.c
 *
 *  Created on: Apr 5, 2018
 *      Author: Jesús Arnoldo Zerecero Núñez
 */

#include "SinCosAngle.h"
#include "SinCosTable.h"

const unsigned short kwSize = sizeof(kaSinTable)/2;

signed short ifnSinValue(unsigned short wAngulo)
{
	if(wAngulo < kwSize) /*Entre 0 y N-1*/
	{
		return kaSinTable[wAngulo];
	}
	else if (wAngulo >= kwSize && wAngulo < kwSize*2 - 1) /*Entre N y 2N-2*/
	{
		return kaSinTable[kwSize*2 - 2 - wAngulo];
	}
	else if (wAngulo >= kwSize*2 && wAngulo < kwSize*3) /*Entre 2N y 3N-1*/
	{
		return kaSinTable[wAngulo - kwSize*2]*-1;
	}
	else if(wAngulo >= kwSize*3 && wAngulo < kwSize*4 - 1) /*Entre 3N y 4N-2*/
	{
		return kaSinTable[kwSize*4 - 2 - wAngulo]*-1;
	}
	else /*Si el ángulo cruza por cero (2N - 1 y 4N - 1), o si se pasa del rango*/
	{
		return 0;
	}
}

signed short ifnCosValue(unsigned short wAngulo)
{
	if(wAngulo < kwSize) /*Entre 0 y N-1*/
	{
		return kaSinTable[kwSize - 1 - wAngulo];
	}
	else if (wAngulo > kwSize && wAngulo <= kwSize*2) /*Entre N + 1 y 2N*/
	{
		return kaSinTable[wAngulo - 1 - kwSize]*-1;
	}
	else if (wAngulo > kwSize*2 && wAngulo < kwSize*3) /*Entre 2N + 1 y 3N-1*/
	{
		return kaSinTable[kwSize*3 - wAngulo - 1]*-1;
	}
	else if(wAngulo > kwSize*3 && wAngulo < kwSize*4) /*Entre 3N + 1 y 4N - 1*/
	{
		return kaSinTable[wAngulo - 1 - kwSize*3];
	}
	else /*Si el ángulo cruza por cero (N y 3N), o si se pasa del rango*/
	{
		return 0;
	}
}

