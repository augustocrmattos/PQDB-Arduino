#include "so.h"
#include "ssd.h"
#include "timer.h"

void setup()
{  
soInit();                      // Inicializa o 74hc
ssdInit();                     // Inicializa display de 7 Seg   
}
int i;
int x = 0;
void loop()
{
 if(x==9999)                   //Reseta o valor de x para que este fique dentro dos valores 0~9999
 {
    x =0;
 }
 ssdDigit(3, x % 10 );          // Unidade
 ssdDigit(2, x / 10 % 10 );     // Dezena
 ssdDigit(1, (x / 100) %10 );   // Centena
 ssdDigit(0, (x / 1000) %10);   // Milhar
 x++;
 for(i=0;i<8;i++)               //Delay
 {
    ssdUpdate();
    timerDelay(5);
 }
}
