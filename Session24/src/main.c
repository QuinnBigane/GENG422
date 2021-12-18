//
// COMP-GENG 422 - Tom Lupfer
//
// Session 24 - I2C Driver Development
//

#include "main.h"
#include "clock.h"
#include "dbg.h"
#include "eprintf.h"
#include "uart.h"


int main(void)
{
	UInt8 RegVal;

	// Initialize the MCU hardware required for debugging first
	ClockInit();
	DbgInit();
	UartInit();

	eprintf("COMP-GENG 422 - I2C driver development\n");

	// Enable the clock for I2C1
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C1);

	// Configure I2C1 for 400KHz
	I2C1->CR2 = 0x0020;		// APB1 freq: 32MHz
	I2C1->CCR = 0x801B;		// Fm mode, Tlow/Thigh: 2, CCR: 27
	I2C1->TRISE = 0x0009;	// Fm mode Trise(Max) = 300nS; 300/31.25 = 9.6, use integer part
	I2C1->CR1 = 0x0001;		// PE: 1 (enable I2C1)

	// Enable the clock for GPIO Port B
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);

	// Configure PB9, PB8 for I2C1 SDA, SCL
	GPIOB->AFR[1] = 0x00000044;		// PB9: AF4 (I2C1_SDA), PB8: AF4 (I2C1_SCL)
	GPIOB->MODER |= 0x000A0000;		// PB9, PB8: alt fcn mode

	// Confirm I2C1 and GPIO registers are being set
	eprintf("CR2:         %04X\n", I2C1->CR2);
	eprintf("CCR:         %04X\n", I2C1->CCR);
	eprintf("TRISE:       %04X\n", I2C1->TRISE);
	eprintf("CR1:         %04X\n", I2C1->CR1);
	eprintf("GPIOB_MODER: %08X\n", GPIOB->MODER);
	eprintf("GPIOB_AFRH:  %08X\n", GPIOB->AFR[1]);

	//Class notes
	//STA, WR I2C ADDR OF DEV,, ACK,, REG ADDR,, ACK,, RPT STA, RD I2C ADDR OF DEV,, ACK,, REG DATA,, NACK/ACK.... ,, STOP
	// figure 213
	//0x30,0f,31,33


	// Enable the clock for GPIO Port A
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);

	// GPIO PA5 -> green LED
	// Configure PA5 as an output, low
	LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_5);
	LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_5, LL_GPIO_MODE_OUTPUT);

	// GPIO PA10 <- user pushbutton
	// Configure PA10 as an input, pulled up
	LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_10, LL_GPIO_MODE_INPUT);
	LL_GPIO_SetPinPull(GPIOA, LL_GPIO_PIN_10, LL_GPIO_PULL_UP);

	//
	// Development polled code to read the LIS2DH12 accelerometer WHO_AM_I register
	//

	//class notes
	//OUT_X_L register 28
	//OUT_X_H register 29
	//etc

	// Generate start
	I2C1->CR1 |= 0x0100;

	// Wait for SB to be set
	while (!(I2C1->SR1 & 0x0001))
		;

	I2C1->DR = 0x30;		// LIS2DH12 addr: 0011000x, x = 0 for write

	// Wait for ADDR to be set
	while (!(I2C1->SR1 & 0x0002))
		;
	I2C1->SR2;				// reading SR2 clears ADDR

	I2C1->DR = 0x0F;		// 0x0F: WHO_AM_I reg

	// Wait for TxE to be set
	while (!(I2C1->SR1 & 0x0080))
		;

	// Generate repeated start
	I2C1->CR1 |= 0x0100;

	// Wait for SB to be set
	while (!(I2C1->SR1 & 0x0001))
		;

	I2C1->DR = 0x31;		// LIS2DH12 addr: 0011000x, x = 1 for read

	// Wait for ADDR to be set
	while (!(I2C1->SR1 & 0x0002))
		;
	I2C1->SR2;				// reading SR2 clears ADDR

	// Wait for RxNE to be set
	while (!(I2C1->SR1 & 0x0040))
		;
	// Read the received data
	RegVal = I2C1->DR;

	// Generate stop
	I2C1->CR1 |= 0x0200;

	// Print out the register value
	eprintf("WHO_AM_I reg: 0x%02X\n", RegVal);

	// Main loop
	while(TRUE)
	{
		// Wait for tick timer
		ClockWaitForTick();

		// Clock the state machines
DBG_SET();

		// Turn on the green LED when the user pushbutton is pressed
		if (LL_GPIO_IsInputPinSet(GPIOA, LL_GPIO_PIN_10))
		{
			LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_5);
		}
		else
		{
			LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_5);
		}

DBG_CLR();

	}	// End - main loop
}
