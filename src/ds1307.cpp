#include "i2c.h"
#include "ds1307.h"

#define DS1307_CTRL_ID (0x68<<1)
#define I2C_WRITE 0
#define I2C_READ 1

// Converte Decimal para BCD
int dec2bcd(int value) {
	return ((value / 10 * 16) + (value % 10));
}
// Converte BCD para Decimal
int bcd2dec(int value) {
	return ((value / 16 * 10) + (value % 16));
}
void dsInit(void) {
	i2cInit();
}
void dsStartClock(void) {
	int seconds;
	//liga o 7o bit
	seconds = dsRead(SEC);
	dsWrite(0x7f & seconds,SEC);
	return;
}
void dsWrite(unsigned char value, int address) {
	i2cWrite(1,0, DS1307_CTRL_ID|I2C_WRITE);
	i2cWrite(0,0,address);
	i2cWrite(0,1,value);
}
int dsRead(int address) {
	int result;
	i2cWrite(1,0,DS1307_CTRL_ID | I2C_WRITE);
	i2cWrite(0,0,address);
	i2cWrite(1,0, DS1307_CTRL_ID | I2C_READ);
	result = i2cRead(1,1 );
	return result;
}
