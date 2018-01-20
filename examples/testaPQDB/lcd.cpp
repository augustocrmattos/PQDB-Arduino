#include "so.h"
#include "io.h"
#include "lcd.h"
#include <Arduino.h>

void lcdCreateChar(int pos, byte line[]){
  lcdCommand(0x40+pos*8);
  for(int i = 0; i<8;i++){
    lcdChar(line[i]);
  }
}
void delayMicro(int a){
	volatile int i;
	for(i=0;i<a;i++);
	//Para chipkit
	//for(i=0;i<(a*10);i++);
}
void delayMili(int a){
	volatile int i;
	for(i=0;i<a;i++){
		delayMicro(1000);
	}
}
//Gera um clock no enable
void pulseEnablePin(){
  digitalWrite(LCD_EN_PIN,HIGH);
  digitalWrite(LCD_EN_PIN,LOW);
}
//Envia 4 bits e gera um clock no enable
void pushNibble(char value, int rs){
  soWrite(value);
  digitalWrite(LCD_RS_PIN,rs);
  pulseEnablePin();
}
//Envia 8 bits em dois pacotes de 4
void pushByte(char value, int rs){
    pushNibble((value >> 4),rs);
    pushNibble((value & 0x0F),rs);
}
void lcdCommand(char value) {
  pushByte(value,LOW);
  if((value==0x01)||(value==0x02)||(value==0x03)){
  delayMili(2);
  }else{
    delayMicro(40);
  }
}
//print the given character at the current cursor position. overwrites, doesn't insert.
void lcdChar(char value) {
  pushByte(value,HIGH);
  delayMicro(40);
}
//imprime um texto (vetor de char)
void lcdString(char msg[]) {
  int i=0;
  while(msg[i]!=0){
    lcdChar(msg[i]);
    i++;
  }
}
// Rotina de incialização
void lcdInit () {
  pinMode(LCD_EN_PIN,OUTPUT);
  pinMode(LCD_RS_PIN,OUTPUT);
  soInit();
  delayMili(15);
  //comunicação começa em 8 bits
  pushNibble(0x03,LOW);
  delayMili(5);
  pushNibble(0x03,LOW);
  delayMicro(160);
  pushNibble(0x03,LOW);
  delayMicro(160);
  // Mudando comunicação para 4 bits
  pushNibble(0x02,LOW);
  delayMicro(100);
  //configura o display
  lcdCommand(0x28);	//8bits, 2 linhas, 5x8
  lcdCommand(0x06);	//modo incremental
  lcdCommand(0x0C);	//display e cursor on, com blink
  lcdCommand(0x03);	//zera tudo
  lcdCommand(0x80);	//posição inicial
  lcdCommand(0x01);	//limpar display
}
