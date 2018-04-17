/*
 * Ecualizador.c
 *
 *  Created on: Jan 21, 2018
 *      Author: Jes�s Arnoldo Zerecero N��ez
 */

#include "Ecualizador.h"
#include "DAC.h"
#include "derivative.h" /* include peripheral declarations */

void vfnEco(unsigned short wValorLeido, unsigned short wBufferSize)
{
	static unsigned short _waEcoBuffer[MAX_POT_VALUE]; /*Se crea un buffer del m�ximo tama�o que pueda dar el pot*/
	static unsigned short *_pEcoBuffer = &_waEcoBuffer[0]; /*Apuntador para recorrer el buffer*/
	unsigned short *pStartingPointerPosition = &_waEcoBuffer[0]; /*Apuntador para guardar la posici�n inicial del buffer*/
	static unsigned short _wCounter = 0; /*Contador para saber cuando se lleg� al final del buffer*/

	if(wBufferSize > 50) /*Si el buffer es muy peque�o, no se ejecutar� el eco o no sonar� bien*/
	{
		*_pEcoBuffer  = *_pEcoBuffer/2 + wValorLeido/2; /*El siguiente dato que ser� guardado en el buffer ser� el valor que ya ten�a el buffer sobre 2 m�s el nuevo valor que se ley� sobre 2*/ 

		vfnDACWrite(*_pEcoBuffer);

		if(_wCounter++ >= wBufferSize) /*Si se lleg� al final del buffer*/
		{
			_pEcoBuffer = pStartingPointerPosition; /*Se reinicia el buffer*/
			_wCounter = 0;
		}
		else
		{
			_pEcoBuffer++; /*Se recorre al siguiente espacio del buffer*/
		}
	}
	else /*Si el pot est� en cero, no se genera eco*/
	{
		vfnDACWrite(wValorLeido);
	}

}

void vfnDistorsion(unsigned short wValorLeido, unsigned short wValorPot)
{
	if(wValorPot > 4095) /*Si el valor del pot se sale del l�mite de 12 bits*/
	{
		wValorPot = 4095; /*Se satura hasta el l�mite*/
	}
	unsigned short wLimite = (4095 - wValorPot)/2; /*Se obtiene el l�mite dentro del cual la se�al no se saturar�*/

	if(wValorLeido > (4095 - wLimite)) /*Si el valor leido supera al l�mite superior*/
	{
		wValorLeido = 4095;
	}
	else if (wValorLeido < wLimite) /*Si el valor leido es menor que el l�mite inferior*/
	{
		wValorLeido = 0;
	}
	vfnDACWrite(wValorLeido);
}

void vfnVibrato(unsigned short wValorLeido, unsigned short wFactorFrecuencia)
{
	static unsigned short _waSawtooth = 0; /*Valor de la se�al de diente de sierra*/
	static unsigned short _wDelay = 0; /*Este delay definir� a la frecuencia con la que se est� multiplicando la se�al original con la diente de sierra*/
	static unsigned short _wVirtualZero = 4095; /*Variable para ajustar el offset de la se�al, por si este no se encuentra en el cero exacto*/
	static unsigned long _dwVibratoResultante = 0; /*Variable para almacenar el resultado de la multiplicaci�n con la diente de sierra*/
	
	
	if(wValorLeido < _wVirtualZero) /*wVirtualZero adquirir� el valor menor de la se�al*/
	{
		_wVirtualZero = wValorLeido;
	}
	wValorLeido = wValorLeido - _wVirtualZero; /*Este valor ser� restado de la se�al para ser ajustada a cero*/
	if(_wDelay++ >= wFactorFrecuencia) /*Si el delay llega a su tope*/
	{
		_dwVibratoResultante = wValorLeido*_waSawtooth; /*Se multiplica por la se�al de diente de sierra*/
		wValorLeido = _dwVibratoResultante >> 12; /*Se recorre para tener un valor de 12 bits*/
		_wDelay = 0;
		if(_waSawtooth++ >= 4095) /*Si se lleg� al tope de la se�al*/
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
