#include "derivative.h"
/*Inicializacion del ADC*/

#define ADC_CANAL_SOUND 0
#define ADC_CANAL_POT 3

void vfnADCInit(void);
/*Funcion para realizar la lectura del ADC*/

unsigned short bfnADCLectura(unsigned char bCanal);
