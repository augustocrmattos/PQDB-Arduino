#include "serial.h"
#include "io.h"


void serialSend(unsigned char c){
  Serial.print(c);
}
unsigned char serialRead(void){
  return Serial.read();
}
void serialInit(void){
  Serial.begin(9600);
}

