#ifndef I2C_H
    #define I2C_H
	void i2cInit(void);
	// Escreve um byte do baramento
	//pode inserir um start antes E/OU um stop no fim
	int i2cWrite(int send_start, int send_stop, unsigned char byte);
	// Lê um byte do baramento
	// Pode enviar um stop no fim
	unsigned char i2cRead(int nack, int send_stop);
#endif

