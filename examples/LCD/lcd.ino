
#include "lcd.h"
#include "so.h"
#include "timer.h"

void setup()
{
soInit();                         // Inicializa o 74hc
lcdInit();                        // Inicializa o LCD
lcdString("Contador LCD : ");     // Escreve uma string no LCD
}
int x = 0;
void loop()
{
    lcdCommand(0xC0);                   //Pula o cursor para a segunda linha
    lcdChar((x / 1000) % 10 + 48);      // Milhar
    lcdChar((x / 100) % 10 + 48);       // Centena
    lcdChar((x / 10) % 10 + 48);        // Dezena
    lcdChar((x / 1) % 10 + 48);         // Unidade
    x++;
    timerDelay(100);
}
