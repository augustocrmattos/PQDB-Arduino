#include "ad.h"
//#include "lcd.h"
#include "keypad.h"
#include "io.h"
#include "nokia5110.h"
#include "console.h"
#include "pwm.h"
#include "rgb.h"
#include "serial.h"
#include "so.h"
#include "ssd.h"
#include "timer.h"
#include "i2c.h"
#include "ds1307.h"


unsigned long tempoAntigo;

void setup() {
  //RTC e LCD

  Serial.begin(115200);
  
  //LCD
  //lcdInit();
  initializeDisplay(0xC0,0x07,0x014);

  //RTC
  dsInit();

  //74HC595
  soInit();

  //Teclado
  kpInit();

  //Timer
  timerInit();

  //Conversor AD
  adInit();

  //Display 7 Seg.
  ssdInit();

  //RGB
  rgbInit();

  //Buzzer
  pwmInit();
  
  turnOff(BLUE);        // Desliga a cor Azul
  turnOn(RED);          // Liga a cor Vermelha
  pwmBuzzer(1000);
  timerDelay(500);      // Delay
  
  turnOff(RED);         // Desliga a cor Azul
  turnOn(GREEN);        // Liga a cor Verde
  pwmBuzzer(1200);
  timerDelay(500);      // Delay
  
  turnOff(GREEN);       // Desliga a cor Verde
  turnOn(BLUE);         // Liga a cor Azul
  pwmBuzzer(1500);
  timerDelay(500);      // Delay

  pwmBuzzer(0);


for(int i=0; i<504; i++) LcdWriteData(0x00); // clear LCD

  dsStartClock();
  dsWrite(0x57,SEC);
  dsWrite(0x59,MIN);
  dsWrite(0x23,HOUR);
  dsWrite(5,WEEKDAY);
  dsWrite(0x08,DAY);
  dsWrite(7,MONTH);
  dsWrite(0x94,YEAR);
  tempoAntigo = millis();
  
}

void loop() {

    int i = 0;
    int k = 0;
    int j = 0;
    int l = 0;

    //LM35
    i = adRead(0);
    i = i - 30;

    LcdXY(0,0);
    LcdWriteCharacter((i / 10) % 10 + 48);
    LcdWriteCharacter((i / 1) % 10 + 48);

    
    //RTC e LCD
    while(millis() - tempoAntigo < 5000) {
    

    i = getHours();

    LcdXY(0,1);
    LcdWriteCharacter((i / 10) % 10 + 48);
      LcdWriteCharacter((i / 1) % 10 + 48);

LcdWriteCharacter(':');

    i = getMinutes();
    LcdWriteCharacter((i / 10) % 10 + 48);
      LcdWriteCharacter((i / 1) % 10 + 48);

LcdWriteCharacter(':');

    i = getSeconds();
    LcdWriteCharacter((i / 10) % 10 + 48);
      LcdWriteCharacter((i / 1) % 10 + 48);
      
LcdXY(0,2);
    i = getDays();
    LcdWriteCharacter((i / 10) % 10 + 48);
      LcdWriteCharacter((i / 1) % 10 + 48);
LcdWriteCharacter('/');

    i = getMonths();
    LcdWriteCharacter((i / 10) % 10 + 48);
      LcdWriteCharacter((i / 1) % 10 + 48);

LcdWriteCharacter('/');

    i = getYears();
    LcdWriteCharacter((i / 10) % 10 + 48);
      LcdWriteCharacter((i / 1) % 10 + 48);
    
    }
    
LcdXY(0,4);
    kpDebounce();                      //Realiza o Debounce do teclado
    for (k = 0; k < 10; k++) {         //Varredura
      if (kpRead() & (1 << k)) {       //Identifica qual tecla foi pressionada
LcdWriteCharacter(k + 48);
        break;
      }
    }
    
    j  = adRead(2);                    // Leitura do POT
    l  = adRead(1);                    //Leitura LDR
    ssdDigit(3, (j / 10) % 10);        // Dezena POT
    ssdDigit(2, (j / 100) % 10);       // Unidade POT
    ssdDigit(1, (l / 10) % 10);        // Dezena LDR
    ssdDigit(0, (l / 100) % 10);       // Unidade LDR
    
    for(j = 0; j < 8; j++){                  // Delay
    ssdUpdate();
    timerDelay(5);
  }
    
}
