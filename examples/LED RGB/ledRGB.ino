#include "timer.h"
#include "rgb.h"

void setup() {
 rgbInit();             // Inicializa o LED RGB
 timerInit();           // Inicializa o Timer
}

void loop() {

  timerDelay(500);      // Delay
  turnOff(BLUE);        // Desliga a cor Azul
  turnOn(RED);          // Liga a cor Vermelha
 
  timerDelay(500);      // Delay
  turnOff(RED);         // Desliga a cor Azul
  turnOn(GREEN);        // Liga a cor Verde
  
  timerDelay(500);      // Delay
  turnOff(GREEN);       // Desliga a cor Verde
  turnOn(BLUE);         // Liga a cor Azul
}
