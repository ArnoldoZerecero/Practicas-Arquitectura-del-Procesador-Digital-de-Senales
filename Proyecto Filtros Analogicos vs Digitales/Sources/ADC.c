#include "ADC.h"

/*Inicializacion del ADC*/

void vfnADCInit(void)
{
	/*Inicializar los clocks*/
	/*ADC 0 reloj*/
    SIM_SCGC6 |= SIM_SCGC6_ADC0_MASK;	
    /*PTB 0 reloj*/
    SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK;	
    /*Puerto E de ADC*/
    PORTE_PCR20 = PORT_PCR_MUX(0); 
    PORTE_PCR22 = PORT_PCR_MUX(0); 
	/* Configuracion ADC*/
    /*Reset*/
    ADC0_CFG1 = 0; 
    ADC0_CFG1 |= (ADC_CFG1_MODE(0) | ADC_CFG1_ADICLK(0) | ADC_CFG1_ADIV(0)) ;	
}
/*Funcion de lectura para el ADC*/

unsigned short bfnADCLectura(unsigned char bCanal)// canal 8 y 9
{
    ADC0_SC1A = ADC_SC1_ADCH(bCanal);  
    /*Conversion del ADC*/
    while(!(ADC0_SC1A & ADC_SC1_COCO_MASK)); 
    {
    }
    return ADC0_RA;
}
