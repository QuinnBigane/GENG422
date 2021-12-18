//
// COMP-GENG 422 - Tom Lupfer
//
// I2C module - polled
//


#include "main.h"
#include "i2c.h"


#define I2C_REQUEST_READ	0x01
#define I2C_REQUEST_WRITE	0x00


void I2cInit(void)
{
	Int DelayCount;

	// Enable the clock for I2C1, delay to take effect
	RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
	for (DelayCount = 0; DelayCount < 10; DelayCount++)
		;

	// Configure I2C1 for 400KHz
	I2C1->CR2 = 0x0020;			// APB1 freq: 32MHz
	I2C1->CCR = 0x801B;			// Fm mode, Tlow/Thigh: 2, CCR: 27
	I2C1->TRISE = 0x0009;		// Fm mode Trise(Max) = 300nS; 300/31.25 = 9.6, use integer part
	I2C1->CR1 = I2C_CR1_PE;		// PE: 1 (enable I2C1)

	// Enable the clock for GPIO Port B, delay to take effect
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
	for (DelayCount = 0; DelayCount < 10; DelayCount++)
		;

	// Configure PB9, PB8 for I2C1 SDA, SCL
	GPIOB->AFR[1] = 0x00000044;		// PB9: AF4 (I2C1_SDA), PB8: AF4 (I2C1_SCL)
	GPIOB->MODER |= 0x000A0000;		// PB9, PB8: alt fcn mode
}


void I2cWriteBuf(UInt8 DevAddr, UInt8 RegAddr, int NumBytes, UInt8 * DataBuf)
{
	// Generate start
	I2C1->CR1 |= I2C_CR1_START;

	// Wait for SB to be set
	while (!(I2C1->SR1 & I2C_SR1_SB))
		;

	// Write device address for a write
	I2C1->DR = DevAddr | I2C_REQUEST_WRITE;

	// Wait for ADDR to be set, then clear it
	while (!(I2C1->SR1 & I2C_SR1_ADDR))
		;
	I2C1->SR2;	// reading SR2 clears ADDR

	// Write register address, wait for completion
	I2C1->DR = RegAddr;
	while (!(I2C1->SR1 & I2C_SR1_TXE))	// Wait for TxE to be set
		;

	// Write data buffer
	while(NumBytes > 0)
	{
		// Write data byte, wait for completion
		I2C1->DR = *DataBuf++;
		while (!(I2C1->SR1 & I2C_SR1_TXE))	// Wait for TxE to be set
			;
		NumBytes--;
	}

	// Generate stop condition
	I2C1->CR1 |= I2C_CR1_STOP;
}


void I2cReadBuf(UInt8 DevAddr, UInt8 RegAddr, int NumBytes, UInt8 * DataBuf)
{
	// Prepare ACK for master to receive data
	I2C1->CR1 |= I2C_CR1_ACK;

	// Generate start
	I2C1->CR1 |= I2C_CR1_START;

	// Wait for SB to be set
	while (!(I2C1->SR1 & I2C_SR1_SB))
		;

	// Write device address for a write
	I2C1->DR = DevAddr | I2C_REQUEST_WRITE;

	// Wait for ADDR to be set, then clear it
	while (!(I2C1->SR1 & I2C_SR1_ADDR))
		;
	I2C1->SR2;	// reading SR2 clears ADDR

	// Write register address, wait for completion
	I2C1->DR = RegAddr;
	while (!(I2C1->SR1 & I2C_SR1_TXE))	// Wait for TxE to be set
		;

	// Generate repeated start
	I2C1->CR1 |= I2C_CR1_START;

	// Wait for SB to be set
	while (!(I2C1->SR1 & I2C_SR1_SB))
		;

	// Write device address for a read
	I2C1->DR = DevAddr | I2C_REQUEST_READ;

	// Wait for ADDR to be set, then clear it
	while (!(I2C1->SR1 & I2C_SR1_ADDR))
		;
	I2C1->SR2;	// reading SR2 clears ADDR

	// Read data into buffer
	while(NumBytes > 0)
	{
		if (NumBytes == 1)
		{
			// Prepare NACK for master to receive last data byte
			I2C1->CR1 &= ~I2C_CR1_ACK;
		}

		// Wait for RxNE to be set
		while (!(I2C1->SR1 & I2C_SR1_RXNE))
			;

		// Read the received data
		*DataBuf++ = I2C1->DR;

		NumBytes--;
	}

	// Generate stop
	I2C1->CR1 |= I2C_CR1_STOP;
}
