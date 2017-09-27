#ifndef IO_H_
#define IO_H_

#include "arduino.h"
/*
#define bitSet(arg,bit) ((arg) |= (1<<bit))
#define bitClr(arg,bit) ((arg) &= ~(1<<bit)) 
#define bitFlp(arg,bit) ((arg) ^= (1<<bit)) 
#define bitTst(arg,bit) ((arg) & (1<<bit)) 

#define OUTPUT 0
#define INPUT  1

#define LOW 0
#define HIGH 1

void pinMode(int pin, int type);
void digitalWrite(int pin, int value);
int digitalRead(int pin);

*/
#define SDA_PIN 18
#define SCL_PIN 19

#define KEYPAD_1_PIN 13
#define KEYPAD_2_PIN 12
#define SO_CLK_PIN   11
#define SO_EN_PIN    10
#define PWM_PIN       9
#define SO_DATA_PIN   8
#define LCD_RS_PIN    7
#define LCD_EN_PIN    6
#define DISP_4_PIN    5
#define LED_BLUE_PIN  4
#define DISP_3_PIN    4 
#define LED_GREEN_PIN 3
#define DISP_2_PIN    3
#define LED_RED_PIN   2
#define DISP_1_PIN    2
#define TX_PIN        1
#define RX_PIN        0


#endif /* IO_H_ */
