/*
 * ADC.c
 *
 *  Created on: Jul 29, 2017
 *      Author: Windows 8.1
 */

#include <stdint.h>
#include "derivative.h"
#include "ADC.h"


void vfnADCInit(ADCConfigInit_t * pADCUserConfig) /*Inicializaci�n, se recibe el apuntador a la estructura*/
{
	SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK; /*Activo clk para puerto E*/
	PORTE_PCR20 = PORT_PCR_MUX(0); /*Activo pin 20 puerto E para entrada de la se�al de ADC, canal DADP0*/
	PORTE_PCR22 = PORT_PCR_MUX(0); /*Activo pin 22 puerto E para entrada de la se�al de ADC, canal DADP3*/

	SIM_SCGC6 |= SIM_SCGC6_ADC0_MASK; /*Activo clk para ADC0*/

	ADC0_CFG1 |= ADC_CFG1_ADIV(pADCUserConfig -> bClkDivision); /*Cu�nto se desea dividir el Bus Clk*/ 
	ADC0_CFG1 |= ((pADCUserConfig -> bSampleTime) << ADC_CFG1_ADLSMP_SHIFT); /*Si se desea muestreo corto o largo*/
	ADC0_CFG1 |= ADC_CFG1_MODE(pADCUserConfig -> bResolucion); /*Selecciona la cantidad de bits de resoluci�n*/

	if (pADCUserConfig -> bSampleTime) /*Si se seleccion� muestreo largo*/
	{
		ADC0_CFG2 |= ADC_CFG2_ADLSTS(pADCUserConfig -> bLongSampleTime); /*Selecciona los ciclos de ADCK que durar� el muestreo largo*/
	}
	
	ADC0_CFG2 |= ((pADCUserConfig -> bHighSpeedConversion) << ADC_CFG2_ADHSC_SHIFT); /*Selecciona si se desea conversi�n de alta o baja velocidad*/

	ADC0_SC3 |= ((pADCUserConfig -> bConversionesContinuas) << ADC_SC3_ADCO_SHIFT); /*Selecciona si se desean coversiones singulares o continuas*/
	ADC0_SC3 |= ((pADCUserConfig -> bEnablePromediado) << ADC_SC3_AVGE_SHIFT); /*Selecciona si se desea promediar las muestras por hardware*/

	if(pADCUserConfig -> bEnablePromediado) /*Si se estar� promediando...*/
	{
		ADC0_SC3 |= ADC_SC3_AVGS(pADCUserConfig -> bMuestrasPromediadas); /*Cu�ntas muestras se desea promediar*/
	}

	ADC0_OFS |= ADC_OFS_OFS(pADCUserConfig -> wOffset); /*Este valor ser� restado del resultado de conversi�n*/
	return;

}


void vfnADCCalibration(void) /*Funci�n de calibraci�n*/
{
	uint16_t wPlusSideCalibrationValue;
	uint16_t wMinusSideCalibrationValue;

	ADC0_SC3 |= ADC_SC3_CAL_MASK; /*Comienza la calibraci�n*/

	wPlusSideCalibrationValue = ADC0_CLP0 + ADC0_CLP1 + ADC0_CLP2 + ADC0_CLP3 + ADC0_CLP4 + ADC0_CLPS; /*Se suman los plus side calibration results*/
	wPlusSideCalibrationValue >> 1; /*Se divide entre 2*/

	ADC0_PG |= ADC_PG_PG(wPlusSideCalibrationValue); /*Se asigna el resultado a la plus side gain*/


	wMinusSideCalibrationValue = ADC0_CLM0 + ADC0_CLM1 + ADC0_CLM2 + ADC0_CLM3 + ADC0_CLM4 + ADC0_CLMS; /*Se suman los minus side calibration results*/
	wMinusSideCalibrationValue >> 1; /*Se divide entre 2*/

	ADC0_MG |= ADC_MG_MG(wMinusSideCalibrationValue); /*Se asigna el resultado a la minus side gain*/

	ADC0_SC3 &= ~ADC_SC3_CAL_MASK; /*Termina la calibraci�n*/

}

uint16_t wfnADCLectura(uint8_t bChannelToUse)
{
	uint16_t wNewAdcValue; /*Valor de retorno*/
	
	ADC0_SC1A = ADC_SC1_ADCH(bChannelToUse); /*Elecci�n del canal*/

	while(!(ADC0_SC1A & ADC_SC1_COCO_MASK)) /*Mientras no se haya terminado la conversi�n*/
	{
		/*Poll*/
	}

	wNewAdcValue = ADC0_RA; /*Se guarda el valor del Result Register en la variable de retorno*/

	ADC0_SC1A = ADC_SC1_ADCH_MASK; /*Se apaga el ADC*/

	return wNewAdcValue;
}

