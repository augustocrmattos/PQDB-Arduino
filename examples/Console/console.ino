#include "console.h"

char string[2] = {'\0', '\0'};         //Conversão de char para string(toda string termina com \0)

void setup()
{
  consoleInit();                       //Inicializa o lcd em modo console
  Serial.begin(9600);                  //Inicializa a serial
  consolePrint("123\n456\n789\n");     //Escreve nas tres primeiras linhas
}

int old;

void loop()
{
  if (Serial.available()) {
    string[0] = Serial.read();          //Lê o buffer de entrada da serial
    if (string[0] == '<') {             //Verifica se o caracter < foi escrito
      consoleMoveLine(-1);              //Move a linha em -1
    } else if (string[0] == '>') {      //Verifica se o caracter < foi escrito
      consoleMoveLine(+1);              //Move a linha em +1
    } else {                            //Caso ambos caracteres nao forem detectados
      consolePrint(string);             //Escreve o que recebeu pela serial
    }
    consoleUpdate();                    //Atualiza LCD
  }
}
