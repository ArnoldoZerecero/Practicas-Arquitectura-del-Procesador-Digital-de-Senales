/*
 * RedNeuronal.c
 *
 *  Created on: Apr 11, 2018
 *      Author: Jes�s Arnoldo Zerecero N��ez
 */
#include "RedNeuronal.h"
#include "FuncionesActivacion.h"


void vfnNeurona(EntradasNeurona_t *psNeuronas)
{	
	while(*psNeuronas->kpwPesos)
	{
		*psNeuronas->pdwResultArray += *(psNeuronas->kpdwInputs++)*(*(psNeuronas->kpwPesos++)); 
	}	
	
	*psNeuronas->pdwResultArray = vfnapFunciones[psNeuronas->kbIndexFuncion](*psNeuronas->pdwResultArray);
}
