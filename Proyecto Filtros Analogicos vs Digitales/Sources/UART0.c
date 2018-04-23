#include "derivative.h"
#include "UART0.h"

//unsigned char gbDataRecieved;
void UART_vfnInitialization(void)
{
	/* Clock Gating UART0 */	
	SIM_SCGC4 |= SIM_SCGC4_UART0_MASK ;
	
	/* Clock Gating Port A */
	SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;
	/* UART0 clock source select / Selects the clock source for the UART0 transmit and receive clock.*/ 
	SIM_SOPT2 |= SIM_SOPT2_UART0SRC(1);
		
	/* MUX as UART0 PTA1RX y PTA2TX */ 
	PORTA_PCR1 |= PORT_PCR_MUX(2);
	PORTA_PCR2 |= PORT_PCR_MUX(2);
	
	/* Ponemos el OSR como 32 bits */
	UART0_C4 = UART0_C4_OSR(26);
	
	/*                 21MHz /(31  + 1) * 68 = 9600 */
	UART0_BDL = 6;
	/*Habilitar transmisor y receptor*/
	UART0_C2 |=  UART_C2_RE_MASK  | UART_C2_TE_MASK;
}

void UART_bfnReceiveBuffer(void)
{
	static unsigned char bReturnValue = 0;
	 /* Esperar a que exista algo para leer */
	  while (!(UART0_S1 & UART0_S1_RDRF_MASK));
	  {
	  /* Regresar lo que llego*/
		  bReturnValue = UART0_D;
		  DAC0_DAT0L = (bReturnValue << 4); /*Se escribe en el DAC el valor leído del UART*/
		  DAC0_DAT0H = (bReturnValue>>4);
	  }
}
void UART_vfnTransmitBuffer(unsigned char bDataToTransmit)
{
	/* Espera a que exista espacio para mandar */
	while(!(UART0_S1 & UART0_S1_TDRE_MASK));
	{
		/*Mandar lo deseado*/
		UART0_D = bDataToTransmit;
	}	
 }
