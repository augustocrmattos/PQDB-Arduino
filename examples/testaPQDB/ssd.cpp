#include "ssd.h"
#include "io.h"
#include "so.h"

//vetor para armazenar a conversao do display
//0gfedcba
//static const char valor[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
//ed0cgafb
static const char valor[] = {
	0xD7, 0x11, 0xCD, 0x5D, 0x1B, 0x5E, 0xDE, 0x15, 0xDF, 0x5F, 0x9F, 0xDA, 0xC6, 0xD9, 0xCE, 0x8E};
//armazena qual e o display disponivel
static char display;
//armazena o valor a ser enviado ao display
static char v0, v1, v2, v3;

void ssdDigit(char position, char value){
	if (position == 0){	v0 = value;	}
	if (position == 1){	v1 = value;	}
	if (position == 2){	v2 = value;	}
	if (position == 3){	v3 = value;	}
}
void ssdUpdate(void){
	//desliga todos os displays
	digitalWrite(DISP_1_PIN,LOW);
	digitalWrite(DISP_2_PIN,LOW);
	digitalWrite(DISP_3_PIN,LOW);
	digitalWrite(DISP_4_PIN,LOW);
	switch(display){ //liga apenas o display da vez
	case 0:
		soWrite(valor[v0]);
		digitalWrite(DISP_1_PIN,HIGH);
		display = 1;
		break;
	case 1:
		soWrite(valor[v1]);
		digitalWrite(DISP_2_PIN,HIGH);
		display = 2;
		break;
	case 2:
		soWrite(valor[v2]);
		digitalWrite(DISP_3_PIN,HIGH);
		display = 3;
		break;
	case 3:
		soWrite(valor[v3]);
		digitalWrite(DISP_4_PIN,HIGH);
		display = 0;
		break;
	default:
		display = 0;
		break;
	}
}
void ssdInit(void){
	soInit();
	pinMode(DISP_1_PIN,OUTPUT);
	pinMode(DISP_2_PIN,OUTPUT);
	pinMode(DISP_3_PIN,OUTPUT);
	pinMode(DISP_4_PIN,OUTPUT);
	v0 = 0;	
	v1 = 1;	
	v2 = 2;	
	v3 = 3;
}


