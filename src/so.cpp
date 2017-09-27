#include "io.h"

void soInit (void){
    pinMode(SO_EN_PIN, OUTPUT);
    pinMode(SO_CLK_PIN, OUTPUT);
    pinMode(SO_DATA_PIN, OUTPUT);
}
void soWrite(int value){
  int i;
  //digitalWrite(SO_CLK_PIN, LOW);
  for (i = 0; i < 8; i++)  {
    digitalWrite(SO_DATA_PIN, !!(value & 0x80));
    digitalWrite(SO_CLK_PIN, HIGH);
    digitalWrite(SO_CLK_PIN, LOW);
    value<<=1;
  }
  digitalWrite(SO_EN_PIN, HIGH); 
  digitalWrite(SO_EN_PIN, LOW);
}
