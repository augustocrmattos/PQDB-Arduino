#include "i2c.h"
#include "io.h"
void i2cInit(void) {
    pinMode(SDA_PIN,INPUT);
    pinMode(SCL_PIN,INPUT);
}

#define I2CSPEED 10
void I2C_delay(void) { volatile int v; int i; for (i=0; i < I2CSPEED/2; i++) v; }
//configura SCL como entrada e retorna o valor do canal
int read_SCL(void){
	pinMode(SCL_PIN,INPUT);
	return digitalRead(SCL_PIN);
}
//configura SDA como entrada e retorna o valor do canal
int read_SDA(void){ 
	pinMode(SDA_PIN,INPUT);
	return digitalRead(SDA_PIN);
}
//Envia um bit zero(0)
void clear_SCL(void){
	pinMode(SCL_PIN,OUTPUT);
	digitalWrite(SCL_PIN,LOW);
}
//Envia um bit um(1)
void set_SDA(void){
	//o bit um é feito colocando o terminal como entrada e permitindo que o pull-up leve o terminal para 1
	pinMode(SDA_PIN,INPUT);
}
//Abaixa o nivel do canal de clock
void clear_SDA(void){
	pinMode(SDA_PIN,OUTPUT);
	digitalWrite(SDA_PIN,LOW);
}
static int started = 0; // armazena é a primeira vez
void i2c_start(void) {
	if (started) {//se já estiver iniciado, prepara para reenviar o bit de start
		set_SDA();
		I2C_delay();
		//Aguarda o clock ficar disponível (clock streching)
		while (read_SCL() == 0);
		I2C_delay();
	}
	// SCL está alto, mudar SDA de 1 para 0
	clear_SDA();
	I2C_delay();
	clear_SCL();
	started = true;
}
void i2c_stop(void){
	clear_SDA();
	I2C_delay();
	// Aguarda o clock ficar disponível (clock streching)
	while (read_SCL() == 0);
	I2C_delay();
	// SCL está alto, mudar SDA de 0 para 1
	set_SDA();
	I2C_delay();
	started = false;
}
// Escreve um bit no barramento
void i2c_write_bit(int bit) {
	if (bit) {
		set_SDA();
	} else {
		clear_SDA();
	}
	I2C_delay();
	while (read_SCL() == 0); // Clock stretching
	I2C_delay();
	clear_SCL();
	I2C_delay();
}
// Lê um bit do barramento
int i2c_read_bit(void) {
	int bit;
	read_SDA();//configura SDA como entrada
	I2C_delay();
	while (read_SCL() == 0); // Clock stretching
	// SCL está alto, o dado está disponível
	bit = read_SDA();
	I2C_delay();
	clear_SCL();
	I2C_delay();
	return bit;
}
// Escreve um byte no barramento I2C.
int i2cWrite(int send_start, int send_stop, unsigned char byte) {
	int bit;
	int nack;
	if (send_start) {
		i2c_start();
	}
	for (bit = 0; bit < 8; bit++) {
		i2c_write_bit((byte & 0x80) != 0);
		byte <<= 1;
	}
	nack = i2c_read_bit();
	if (send_stop) {
		i2c_stop();
	}
	return nack;
}
// Lê um byte do barramento I2C
unsigned char i2cRead(int nack, int send_stop) {
	unsigned char byte = 0;
	unsigned int bit;
	for (bit = 0; bit < 8; bit++) {
		byte = (byte << 1) | i2c_read_bit();
	}
	i2c_write_bit(nack);
	if (send_stop) {
		i2c_stop();
	}
	return byte;
}
