#include "ad.h"
#include "so.h"
#include "ssd.h"
#include "timer.h"
void setup()
{
adInit();                              // Inicializa o adc
soInit();                              // Inicializa o 74hc
ssdInit();                             // Inicializa o Display de 7 Segmentos
}
int i;
void loop()
{
    i  = adRead(2);                    // Leitura do POT
    ssdDigit(3, (i / 10) % 10);        // Dezena
    ssdDigit(2, (i / 100) % 10);       // Unidade
    ssdDigit(1,0);                     // 0
    ssdDigit(0,0);                     // 0
    for(i=0;i<8;i++){                  // Delay
    ssdUpdate();
    timerDelay(5);
  }
}
