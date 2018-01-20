#include "nokia5110.h"
#include <Arduino.h>
#include <avr/pgmspace.h>

void initializeDisplay(byte vop, byte tempCoef, byte bias)
{
  pinMode(RST, OUTPUT);
  pinMode(DC, OUTPUT);
  pinMode(DIN, OUTPUT);
  pinMode(CLK, OUTPUT);
  digitalWrite(RST, LOW);
  digitalWrite(RST, HIGH);

  LcdWriteCmd(0x21);  // LCD extended commands 0010 0001 --- 0010 PD V H   PowerDown = 0, V = 0, H = 1
  //V = 0 para ativar escrita horizontal
  //H = 1 para ativar comandos adicionais
  
  LcdWriteCmd(vop);  // set LCD Vop (contrast) 1011 1111 Constrate setado para C0 = 5V
//Example: If user wants value of VLCD at 5 volt
//5 = 3.06 + (VOP6 to VOP0) x 0.06
//(VOP6 to VOP0) = (5 - 3.06) / 0.06
// (VOP6 to VOP0) = 32.33 approximately 32 (20H) or 0100000B
//So, the command that will be sent to LCD to set value of VOP
//is 11000000B or C0H. 

  LcdWriteCmd(tempCoef);  // set temp coefficent 0000 0100 Coeficiente de temperatura para o 3
  //empirico
  
  LcdWriteCmd(bias);  // LCD bias mode 1:40 0001 0100
  //Valor ótimo dado pelo datasheet
  
  LcdWriteCmd(0x20);  // LCD basic commands 0010 0000
  //retornar para os comandos básicos
  
  LcdWriteCmd(0x0C);  // LCD normal video 0000 1100
  //Coloca o LCD no modo normal
}

void LcdWriteString(char *characters)
{
  while(*characters) LcdWriteCharacter(*characters++);
}

void LcdWriteCharacter(char character)
{
  for(int i=0; i<5; i++) {

    byte temp = pgm_read_byte_near(ASCII + ((character - 0x20)*5) + i);
    Serial.println(temp,HEX);
    LcdWriteData(temp);
  }
  LcdWriteData(0x00);
}

void LcdWriteData(byte dat)
{
  digitalWrite(DC, HIGH); //DC pin is low for commands
  shiftOut(DIN, CLK, MSBFIRST, dat); //transmit serial data
}

void LcdXY(int x, int y)
{
  LcdWriteCmd(0x80 | x);  // Column.
  LcdWriteCmd(0x40 | y);  // Row.
}

void LcdWriteCmd(byte cmd)
{
  digitalWrite(DC, LOW); //DC pin is low for commands
  shiftOut(DIN, CLK, MSBFIRST, cmd); //transmit serial data
}