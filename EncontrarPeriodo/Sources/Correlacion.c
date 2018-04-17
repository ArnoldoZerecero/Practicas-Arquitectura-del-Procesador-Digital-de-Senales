/*
 * Correlacion.c
 *
 *  Created on: Mar 4, 2018
 *      Author: Jesús Arnoldo Zerecero Núñez
 */

#include "Correlacion.h"


unsigned long* pdwfnCorrelacion (unsigned char * pbBufferSistema, unsigned char * pbBufferEntrada)
{
	unsigned short wInstancias = SIZE; /*Contador del ciclo principal*/
	unsigned short wCounter = 0; /*Contador para los ciclos de sumas de productos*/
	unsigned short wSoPsCounter = 0; /*Contador de las sumas de productos que se harán/hicieron*/
	static unsigned long dwaResultado[SIZE*2 - 1] = {0}; /*Arreglo de retorno*/
	unsigned long *pdwResultado = &dwaResultado[0];

	while(wInstancias--) /*Se hace la mitad de la correlación*/
	{
		*pdwResultado = 0;
		wCounter = ++wSoPsCounter; /*Se lleva la cuenta de cuantas sumas de productos deben hacerse ahora*/
		while (wCounter--) 
		{
			*pdwResultado += (unsigned short)(((unsigned short)*pbBufferSistema++)*((unsigned short)*pbBufferEntrada++));
		}
		pbBufferSistema -=  wSoPsCounter; /*Se regresan los apuntadores a la posición debida para la siguiente suma de productos*/
		pbBufferEntrada -=  wSoPsCounter + 1;
		pdwResultado++;
	}
	
	wInstancias = SIZE - 1;
	while(wInstancias--) /*Se hace la otra mitad de la correlación*/
	{
		*pdwResultado = 0;
		pbBufferSistema += wSoPsCounter - 1; /*Se regresan los apuntadores a la posición debida para la siguiente suma de productos*/
		pbBufferEntrada += wSoPsCounter - 1;
		wCounter = --wSoPsCounter; /*Se lleva la cuenta de cuantas sumas de productos deben hacerse ahora*/
		while (wCounter--) 
		{
			*pdwResultado += (unsigned short)(((unsigned short)*pbBufferSistema--)*((unsigned short)*pbBufferEntrada--));
		}
		pbBufferSistema++; /*Se incrementa una última vez este apuntador debido a que no se utilizará otro de sus elementos (se multiplicaría por cero)*/
		pdwResultado++;
	}
	return dwaResultado;
}

unsigned long dwfnFindEnergy(unsigned long * pdwCorrelacion, unsigned short wSize)
{
	unsigned long dwCorrMax = 0;

	while(wSize--)
	{
		if(*pdwCorrelacion++ > dwCorrMax) /*Se busca el valor máximo del arreglo*/
		{
			dwCorrMax = *pdwCorrelacion;
		}
	}
	return dwCorrMax;
}

unsigned short wfnFindMaxPeakLocation(unsigned long * pdwCorrelacion, unsigned short wSize)
{
	unsigned long dwCorrMax = 0;
	unsigned short wLocation = 0;

	while(wSize--)
	{
		if(*pdwCorrelacion++ > dwCorrMax) /*Se busca el valor máximo del arreglo*/
		{
			dwCorrMax = *pdwCorrelacion;
			wLocation = (SIZE*2 - 1) - wSize; /*Se almacena la posición en el buffer del valor máximo que se encuentre*/
		}

	}
	return wLocation;
}


unsigned short wfnFindPeriod(unsigned long * pdwCorrelacion,  unsigned short wSize)
{
	/*Variables para la resta entre cada 2 picos encontrados*/
	unsigned short wPeakLocation1 = 0; 
	unsigned short wPeakLocation2 = 0;
	unsigned short wDiferencia = 0;
	unsigned short wCounter = wSize;
	
	/*Buffer para almacenar las diferencias entre picos encontrados*/
	unsigned short waPeaks[300];
	unsigned short *pwPeaks = &waPeaks[0];
	
	/*Contadores para comparar cada elemento del buffer de picos encontrados entre sí*/
	unsigned short wElementosEnBuffer = 0;
	unsigned short wCounterAux = 0;
	
	/*Variables para el cálculo de moda de las diferencias entre los picos encontrados*/
	unsigned short wDiferenciaAccum = 0;
	unsigned short wDiferenciasTop = 0;
	unsigned short wModa = 0;

	while(wCounter--)
	{
		if(*pdwCorrelacion > *(pdwCorrelacion - 1) && *pdwCorrelacion > *(pdwCorrelacion + 1)) /*Si el valor actual es mayor a los valores adyacentes*/
		{
			if(wPeakLocation1 == wPeakLocation2) /*Se almacena la posición del primer pico encontrado*/
			{
				wPeakLocation1 = wSize - wCounter;
			}
			else
			{
				wPeakLocation2 = wSize - wCounter; /*Se almacena la posición del segundo pico encontrado*/
				if(wPeakLocation1 > wPeakLocation2)
				{
					wDiferencia = wPeakLocation1 - wPeakLocation2;
				}
				else
				{
					wDiferencia = wPeakLocation2 - wPeakLocation1;
				}
				*pwPeaks = wDiferencia; /*Se guarda la distancia entre los picos en el buffer*/
				wElementosEnBuffer++; /*Contador de cuántos elementos tiene el buffer*/
				wCounterAux = wElementosEnBuffer;
				pwPeaks = &waPeaks[0];
				while(wCounterAux--) 
				{
					if(wDiferencia == *pwPeaks) /*Si la diferencia encontrada se encuentra repetida en el buffer*/
					{
						wDiferenciaAccum++; /*Se acumulan cuántas veces se repitió ese valor*/
					}
					pwPeaks++;
				}
				
				if(wDiferenciaAccum > wDiferenciasTop) /*Si la diferencia es la que se encuentra más veces repetida en el buffer*/
				{
					wDiferenciasTop = wDiferenciaAccum; /*Nuevo valor a vencer*/
					wModa = wDiferencia; /*Ese valor será la moda*/
				}
				wPeakLocation1 = wPeakLocation2; /*Se recorren las posiciones encontradas de los picos para comparar con la siguiente que se encuentre*/
			}
		}
		pdwCorrelacion++;
	}

	if(wDiferenciaAccum != wDiferenciasTop) /*Cuando el periodo de la señal de entrada es menor a 1ms, la moda detectada es errónea. Se regresará un 1 en ese caso*/
	{
		return 2;
	}
	else
	{
		return wModa;
	}
}
