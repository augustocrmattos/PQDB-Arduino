
#include "lcd.h"
#include "keypad.h"
#include "timer.h"

void setup(){
  lcdInit();                             //Inicializa o LCD
  kpInit();                              //Inicializa o teclado
  timerInit();                           //Inicializa o Timer
  lcdString("Projeto Catarse");          //Escreve uma string no LCD
  lcdCommand(0xC0);                      //Pula o cursos para segunda linha e primeira coluna
  lcdString("Tecla:");                   //Escreve uma string no LCD 
}
int i;
void loop() {
    lcdCommand(0xC7);                  //Pula o cursos para segunda linha e oitava coluna
    kpDebounce();                      //Realiza o Debounce do teclado
    for (i = 0; i < 10; i++) {         //Varredura
      if (kpRead() & (1 << i)) {       //Identifica qual tecla foi pressionada
        lcdChar(i + 48);               //Escreve qual tecla foi escrita
        break;
      }
    }
 }
