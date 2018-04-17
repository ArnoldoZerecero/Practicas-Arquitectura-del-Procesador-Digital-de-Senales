/*
 * DAC.c
 *
 *  Created on: Nov 26, 2017
 *      Author: Jesús Arnoldo Zerecero Núñez
 */

#include "DAC.h"
#include "derivative.h" 


void vfnDACGPIOInit(void)
{
	SIM_SCGC6 |= SIM_SCGC6_DAC0_MASK;
	SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK;

	PORTE_PCR30 |= PORT_PCR_MUX(0); /*Pin de salida del DAC*/
}


void vfnDACInitConfig(void)
{	
	DAC0_C0 |= DAC_C0_DACEN_MASK; /*DAC Enable*/
}

void vfnDACWrite(unsigned short wValue)
{
	DAC0_DAT0L = wValue; /*Se divide el valor, 4 bits en la parte HIGH y 8 bits en la parte LOW del registro de DAT0 del DAC para una resolución de 12 bits*/
	DAC0_DAT0H = wValue >> 8; 
}


void vfnSignalOnOff(void)
{
	static unsigned char flgOnOff = 1; /*Bandera pasa saber si la señal está prendida (1) o apagada (0)*/
	if(flgOnOff)
	{
		DAC0_C0 &= ~DAC_C0_DACEN_MASK; /*Se apaga el DAC enable*/
		flgOnOff = 0;
	}
	else
	{
		DAC0_C0 |= DAC_C0_DACEN_MASK; /*Se prende el DAC enable*/
		flgOnOff = 1;
	}
}

