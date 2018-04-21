///////////////////////////////////////////////////////////////////////////////////////////////////
//                                      Includes Section
///////////////////////////////////////////////////////////////////////////////////////////////////
#include <stdint.h>
#include <stddef.h>
#include "derivative.h"
#include "PIT.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
//                                   Defines & Macros Section
///////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////
//                                       Typedef Section
///////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////
//                                  Function Prototypes Section
///////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////
//                                   Global Constants Section
///////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////
//                                   Static Constants Section
///////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////
//                                   Global Variables Section
///////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////
//                                   Static Variables Section
///////////////////////////////////////////////////////////////////////////////////////////////////

static PitCallback AppCallback;

///////////////////////////////////////////////////////////////////////////////////////////////////
//                                      Functions Section
///////////////////////////////////////////////////////////////////////////////////////////////////


void vfnPitInit(uint32_t dwTimeOut,  PitCallback ApplicationCallback)
{
	/* enable the PIT clock */
	SIM_SCGC6 |= SIM_SCGC6_PIT_MASK;
	
	/* Enable PIT interrupt to CPU */
	//NVIC_ISER |= (1<<22);
	
	/* Enable the PIT module and the debug mode */
	PIT_MCR &= ~PIT_MCR_MDIS_MASK;
	PIT_MCR |= PIT_MCR_FRZ_MASK;
	/* Load the target count to the Counter0 */
	PIT_LDVAL0 = dwTimeOut;

	/* Enable interrupts */
	//PIT_TCTRL0 |= PIT_TCTRL_TIE_MASK;
	
	if(ApplicationCallback != NULL)
	{
		AppCallback = ApplicationCallback;
	}
}

void vfnPitStart(void)
{
	/* Start the counter */
	PIT_TCTRL0 |= PIT_TCTRL_TEN_MASK;
}

void vfnPitStop(void)
{
	/* stop the timer */
	PIT_TCTRL0 &= ~PIT_TCTRL_TEN_MASK;
}

void PIT_IRQHandler(void)
{
	/* clear PIT flag */
	PIT_TFLG0 |= PIT_TFLG_TIF_MASK;
	
	AppCallback();
}



///////////////////////////////////////////////////////////////////////////////////////////////////
// EOF
///////////////////////////////////////////////////////////////////////////////////////////////////

