//
// COMP-GENG 422 - Tom Lupfer
//
// I2C module header file
//

void I2cInit(void);
void I2cWriteBuf(UInt8 DevAddr, UInt8 RegAddr, int NumBytes, UInt8 * DataBuf);
void I2cReadBuf(UInt8 DevAddr, UInt8 RegAddr, int NumBytes, UInt8 * DataBuf);
