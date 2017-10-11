#include "ssd.h"
#include "so.h"

void setup() {
  soInit();
  ssdInit();
}
int cont = 0, seg = 0, minutos = 0, hora = 0;

void loop() { //Loop que toma aproximadamente 11,9ms para ser executado.
  if(cont >=84) //11,9*84 = 999,6 ~ 1000ms = 1s
  {
    seg++;
    cont = 0;
  }
  if(seg>=60)
  {
    minutos++;
    seg = 0;
  }
  if(minutos>=60)
  {
    hora++;
    minutos = 0;
  }
  if(hora>=24)
  {
    hora=0;
  }
  
  //Exibe o tempo
  ssdDigit(0,(hora/10)%10);
  ssdDigit(1,hora%10);
  ssdDigit(2,(minutos/10)%10);
  ssdDigit(3,minutos%10);
  cont++;
  ssdUpdate();
}
