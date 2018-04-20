/*
 * main implementation: use this 'C' sample to create your own application
 *
 */

#include "derivative.h" /* include peripheral declarations */
#include "RedNeuronal.h"
#include "FuncionesActivacion.h"

/*CASO DE PRUEBA. ARREGLO NEURONAL 3-5-2*/

#define SIZE_CAPA_1 3
#define SIZE_CAPA_2 5
#define SIZE_CAPA_3 2

int main(void)
{
	/*NOTA: El usuario debe conocer la secuencia en la que operarán todas la neuronas, ya que estos arreglos se basan en el orden de ejecución*/

	const unsigned short kwaPesosEntradas[SIZE_CAPA_1][2] = {	/*Se asume que estos valores son los finales para la red neuronal (después de entrenar), es por ello que son constantes*/
			{1,0},
			{10,0},
			{100,0}
	};
	const unsigned short kwaPesosCapa2[SIZE_CAPA_2][SIZE_CAPA_1 + 1] = {
			{10,10,10,0},
			{100,100,1,0},
			{1,10,10,0},
			{10,100,100,0},
			{1000,1000,1,0}
	};
	const unsigned short kwaPesosCapa3[SIZE_CAPA_3][SIZE_CAPA_2 + 1] = {
			{1,10,100,1000,1000,0},
			{1,1,1,10,100,0}
	};

	const unsigned long kdwaSystemInputs[]= {5,10,15}; /*Entradas del sistema*/

	/*Buffers para almacenar resultados y pasarlos entre capas*/
	unsigned long dwaResultCapa1[SIZE_CAPA_1] = {0};
	unsigned long dwaResultCapa2[SIZE_CAPA_2]= {0};
	unsigned long dwaResultCapa3[SIZE_CAPA_3]= {0};

	EntradasNeurona_t saInitNeuronas[] = { /*Inicialización de red neuronal*/
			{BYPASS, &kdwaSystemInputs[0], &kwaPesosEntradas[0][0], &dwaResultCapa1[0]},
			{BYPASS, &kdwaSystemInputs[1], &kwaPesosEntradas[1][0], &dwaResultCapa1[1]},
			{BYPASS, &kdwaSystemInputs[2], &kwaPesosEntradas[2][0], &dwaResultCapa1[2]},
			{LOGSIG, &dwaResultCapa1[0], &kwaPesosCapa2[0][0], &dwaResultCapa2[0]},
			{LOGSIG, &dwaResultCapa1[0], &kwaPesosCapa2[1][0], &dwaResultCapa2[1]},
			{LOGSIG, &dwaResultCapa1[0], &kwaPesosCapa2[2][0], &dwaResultCapa2[2]},
			{LOGSIG, &dwaResultCapa1[0], &kwaPesosCapa2[3][0], &dwaResultCapa2[3]},
			{LOGSIG, &dwaResultCapa1[0], &kwaPesosCapa2[4][0], &dwaResultCapa2[4]},
			{PURELIN, &dwaResultCapa2[0], &kwaPesosCapa3[0][0], &dwaResultCapa3[0]},
			{PURELIN, &dwaResultCapa2[0], &kwaPesosCapa3[1][0], &dwaResultCapa3[1]},
			{0,0,0,0} /*Encontrar un cero indica el final del arreglo de neuronas*/
	};
	
	EntradasNeurona_t *psNeuronas = &saInitNeuronas[0];

	for(;;) 
	{	   
		while(psNeuronas->pdwResultArray) /*Encontrar un cero indica el final del arreglo de neuronas*/
		{
			vfnNeurona(psNeuronas++);
		}
	}
	
	return 0;
}
