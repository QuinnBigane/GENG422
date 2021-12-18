//
// COMP-GENG 422 - Tom Lupfer
//
// Debug module
//

#include "main.h"
#include "dbg.h"


void DbgInit(void)
{
	// Enable the clock for GPIO Port C
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);

	// GPIO PC4 -> Debug pin
	// Initialize PC4 to an output, low
	LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_4);
	LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_4, LL_GPIO_MODE_OUTPUT);
}
