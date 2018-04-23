/*
 * DAC.h
 *
 *  Created on: Nov 27, 2017
 *      Author: User
 */

#ifndef DAC_H_
#define DAC_H_

#include "derivative.h" /* include peripheral declarations */

void vfndac_Init(void);
void vfndac_Output(unsigned short wValue);
#endif /* DAC_H_ */
