//
// COMP-GENG 422 - Tom Lupfer
//
// Session 21 - I2C Driver Development
//

#include "main.h"
#include "clock.h"
#include "dbg.h"
#include "eprintf.h"
#include "uart.h"


int main(void)
{
	// Initialize the MCU hardware required for debugging first
	ClockInit();
	DbgInit();
	UartInit();

//	eprintf("COMP-GENG 422 - I2C driver development\n");
//	eprintf("TRISE: %8b\n", I2C1->TRISE);


	// Enable clock for GPIO B
	LL_APB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);

	//Enable alternative function for PB8/9
	GPIOB->MODER |= 0x000A0000;
	GPIOB->AFR[1] = 0x00000044;

//	eprintf("GBIOB Mode Register: %8b\n", GPIOB->MODER);
//	eprintf("GBIOB AFR[1] Register: %8b\n", GPIOB->AFR[1]);


	//Enable cock for I2C
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C1);

	I2C1->CR2 = 0x0020; 	//APB1 freq 32MHz
	I2C1->CCR = 0x801B;		//FN mode Tlow/Thi, 27
	I2C1->TRISE = 0x0009;	//
	I2C1->CR1 = 0x0001;		//Enable Start bit

//	eprintf("CR2: %8b\n", I2C1->CR2);
//	eprintf("CCR: %8b\n", I2C1->CCR);
//	eprintf("TRISE: %8b\n", I2C1->TRISE);
//	eprintf("CR1: %8b\n", I2C1->CR1);

	I2C1->CR1 |= 0x0100;	//start 1
	// Main loop
	//Falling, trigger level 1V, Channel 1/2 1 volt per division,
	//  offset channel 2 by -4, timebase to 100 micro seconds per divide,
	while(TRUE)
	{
		// Wait for tick timer
		ClockWaitForTick();

		// Clock the state machines0009
		DBG_SET();
		DBG_CLR();

	}	// End - main loop
}


/*
 * I2C1
 * 		- set up registers
 * 		- set up clocks
 * 		- initiate START
 *
 * 		SCL -> PB8 (AFIO4)
 * 		SCA -> PB9 (AFIO4)
 *
 * 		Set AFRH8/AFRH9[3:0] = 0100
 *
 *
 */
