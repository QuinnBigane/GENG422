//
// COMP-GENG 422 - Tom Lupfer
//
// Session 26 - Polled I2C Driver Example
//

#include "main.h"
#include "clock.h"
#include "dbg.h"
#include "eprintf.h"
#include "i2c.h"
#include "uart.h"


#define LIS2DH12_I2C_ADDR				0x30

#define LIS2DH12_WHO_AM_I_REG_ADDR		0x0f
#define LIS2DH12_CTRL_REG1_REG_ADDR		0x20
#define LIS2DH12_CTRL_REG2_REG_ADDR		0x21

#define LIS2DH12_REG_ADDR_AUTO_INCR		0x80


int main(void)
{
	UInt8 RegVal;
	UInt8 RdBuf[2];
	UInt8 WrBuf[2];

	// Initialize the MCU hardware required for debugging first
	ClockInit();
	DbgInit();
	I2cInit();
	UartInit();

	eprintf("COMP-GENG 422 Session 26 - Polled I2C Driver\n");

	I2cReadBuf(LIS2DH12_I2C_ADDR, LIS2DH12_WHO_AM_I_REG_ADDR, 1, &RegVal);
	eprintf("LIS2DH12 WHO_AM_I  register: 0x%02X\n", RegVal);

	I2cReadBuf(LIS2DH12_I2C_ADDR, LIS2DH12_CTRL_REG1_REG_ADDR, 1, &RegVal);
	eprintf("LIS2DH12 CTRL_REG1 register: 0x%02X\n", RegVal);

	RegVal = 0xaa;
	I2cWriteBuf(LIS2DH12_I2C_ADDR, LIS2DH12_CTRL_REG1_REG_ADDR, 1, &RegVal);
	I2cReadBuf(LIS2DH12_I2C_ADDR, LIS2DH12_CTRL_REG1_REG_ADDR, 1, &RegVal);
	eprintf("LIS2DH12 CTRL_REG1 register: 0x%02X\n", RegVal);

	RegVal = 0x55;
	I2cWriteBuf(LIS2DH12_I2C_ADDR, LIS2DH12_CTRL_REG1_REG_ADDR, 1, &RegVal);
	I2cReadBuf(LIS2DH12_I2C_ADDR, LIS2DH12_CTRL_REG1_REG_ADDR, 1, &RegVal);
	eprintf("LIS2DH12 CTRL_REG1 register: 0x%02X\n", RegVal);

	I2cReadBuf(LIS2DH12_I2C_ADDR, LIS2DH12_CTRL_REG1_REG_ADDR | LIS2DH12_REG_ADDR_AUTO_INCR, 2, RdBuf);
	eprintf("LIS2DH12 CTRL_REG1 register: 0x%02X\n", RdBuf[0]);
	eprintf("LIS2DH12 CTRL_REG2 register: 0x%02X\n", RdBuf[1]);

	WrBuf[0] = 0xbe;
	WrBuf[1] = 0xef;
	I2cWriteBuf(LIS2DH12_I2C_ADDR, LIS2DH12_CTRL_REG1_REG_ADDR | LIS2DH12_REG_ADDR_AUTO_INCR, 2, WrBuf);
	I2cReadBuf(LIS2DH12_I2C_ADDR, LIS2DH12_CTRL_REG1_REG_ADDR | LIS2DH12_REG_ADDR_AUTO_INCR, 2, RdBuf);
	eprintf("LIS2DH12 CTRL_REG1 register: 0x%02X\n", RdBuf[0]);
	eprintf("LIS2DH12 CTRL_REG2 register: 0x%02X\n", RdBuf[1]);

	// Main loop
	while(TRUE)
	{
		// Wait for tick timer
		ClockWaitForTick();

		// Clock the state machines
DBG_SET();

		// State machines clocked here

DBG_CLR();
	}	// End - main loop
}
