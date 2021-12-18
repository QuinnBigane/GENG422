//
// COMP/GENG 421 - Tom Lupfer
//
// Session 1 – LED blink via software delay loop
//
// GPIO B4 -> Red LED (active low)
//

#include "stm32l1xx.h"
#include "stm32l1xx_nucleo.h"
#include "stm32l1xx_ll_bus.h"
#include "stm32l1xx_ll_gpio.h"

//             ^    ^
//             |    |
//             |    ell ell --> low-level driver
//             |
//             ell one -------> STM32L1xx family of microprocessors


#define FALSE	0
#define TRUE	1


int main(void)
{
	volatile int DelayCnt;

	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);
	LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_4);
	LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_4, LL_GPIO_MODE_OUTPUT);

	// Main loop
	while(TRUE)
	{
		LL_GPIO_TogglePin(GPIOB, LL_GPIO_PIN_4);

		for (DelayCnt = 0; DelayCnt < 20000; DelayCnt++)
			;
	}	// End - main loop
}
