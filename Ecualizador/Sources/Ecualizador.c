/*
 * Ecualizador.c
 *
 *  Created on: Jan 21, 2018
 *      Author: Jesús Arnoldo Zerecero Núñez
 */

#include "Ecualizador.h"
#include "DAC.h"
#include "derivative.h" /* include peripheral declarations */

void vfnEco(unsigned short wValorLeido, unsigned short wBufferSize)
{
	static unsigned short _waEcoBuffer[MAX_POT_VALUE]; /*Se crea un buffer del máximo tamaño que pueda dar el pot*/
	static unsigned short *_pEcoBuffer = &_waEcoBuffer[0]; /*Apuntador para recorrer el buffer*/
	unsigned short *pStartingPointerPosition = &_waEcoBuffer[0]; /*Apuntador para guardar la posición inicial del buffer*/
	static unsigned short _wCounter = 0; /*Contador para saber cuando se llegó al final del buffer*/

	if(wBufferSize > 50) /*Si el buffer es muy pequeño, no se ejecutará el eco o no sonará bien*/
	{
		*_pEcoBuffer  = *_pEcoBuffer/2 + wValorLeido/2; /*El siguiente dato que será guardado en el buffer será el valor que ya tenía el buffer sobre 2 más el nuevo valor que se leyó sobre 2*/ 

		vfnDACWrite(*_pEcoBuffer);

		if(_wCounter++ >= wBufferSize) /*Si se llegó al final del buffer*/
		{
			_pEcoBuffer = pStartingPointerPosition; /*Se reinicia el buffer*/
			_wCounter = 0;
		}
		else
		{
			_pEcoBuffer++; /*Se recorre al siguiente espacio del buffer*/
		}
	}
	else /*Si el pot está en cero, no se genera eco*/
	{
		vfnDACWrite(wValorLeido);
	}

}

void vfnDistorsion(unsigned short wValorLeido, unsigned short wValorPot)
{
	if(wValorPot > 4095) /*Si el valor del pot se sale del límite de 12 bits*/
	{
		wValorPot = 4095; /*Se satura hasta el límite*/
	}
	unsigned short wLimite = (4095 - wValorPot)/2; /*Se obtiene el límite dentro del cual la señal no se saturará*/

	if(wValorLeido > (4095 - wLimite)) /*Si el valor leido supera al límite superior*/
	{
		wValorLeido = 4095;
	}
	else if (wValorLeido < wLimite) /*Si el valor leido es menor que el límite inferior*/
	{
		wValorLeido = 0;
	}
	vfnDACWrite(wValorLeido);
}

void vfnVibrato(unsigned short wValorLeido, unsigned short wFactorFrecuencia)
{
	static unsigned short _waSawtooth = 0; /*Valor de la señal de diente de sierra*/
	static unsigned short _wDelay = 0; /*Este delay definirá a la frecuencia con la que se esté multiplicando la señal original con la diente de sierra*/
	static unsigned short _wVirtualZero = 4095; /*Variable para ajustar el offset de la señal, por si este no se encuentra en el cero exacto*/
	static unsigned long _dwVibratoResultante = 0; /*Variable para almacenar el resultado de la multiplicación con la diente de sierra*/
	
	
	if(wValorLeido < _wVirtualZero) /*wVirtualZero adquirirá el valor menor de la señal*/
	{
		_wVirtualZero = wValorLeido;
	}
	wValorLeido = wValorLeido - _wVirtualZero; /*Este valor será restado de la señal para ser ajustada a cero*/
	if(_wDelay++ >= wFactorFrecuencia) /*Si el delay llega a su tope*/
	{
		_dwVibratoResultante = wValorLeido*_waSawtooth; /*Se multiplica por la señal de diente de sierra*/
		wValorLeido = _dwVibratoResultante >> 12; /*Se recorre para tener un valor de 12 bits*/
		_wDelay = 0;
		if(_waSawtooth++ >= 4095) /*Si se llegó al tope de la señal*/
		{
			_waSawtooth = 0;
		}
	}

	vfnDACWrite(wValorLeido);
}

void vfnInvertido(unsigned short wValorLeido)
{
	if(wValorLeido < 2048)
	{
		wValorLeido = 2047 - wValorLeido; /*4095 - 2048 - wValorLeido*/
	}
	else
	{
		wValorLeido = wValorLeido - 2048;
	}
	vfnDACWrite(wValorLeido);
}
