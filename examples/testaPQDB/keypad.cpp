#include "keypad.h"
#include "so.h"
#include "io.h"

static unsigned int keys;

//vetor com o "nome" dos bot�es
//U -> up, L -> left, D -> down, R -> right
//S -> start, s -> select
//a ordem � referente a posi��o dos bot�es
static const char charKey[] = {'U','L','D','R','S','S','S','A','B','s'};

unsigned int kpRead(void) {

    return keys;
}
char kpReadKey(void){
  int i;
  
      kpDebounce();                      //Realiza o Debounce do teclado
    for (i = 0; i < 10; i++) {         //Varredura
      if (kpRead() & (1 << i)) {       //Identifica qual tecla foi pressionada
              Serial.println(i);
      Serial.println(charKey[i]);
        return charKey[i];             //Escreve qual tecla foi escrita
  //nenhuma tecla pressionada
}
    }
}

void kpDebounce(void) {
    unsigned char i;
    static unsigned char tempo;
    static unsigned int newRead;
    static unsigned int oldRead;
    newRead = 0;
    for(int i = 0; i<5; i++){
      soWrite(1<<(i+3));
      if(digitalRead(KEYPAD_1_PIN)){
        bitSet(newRead,i);
      }
      if(digitalRead(KEYPAD_2_PIN)){
        bitSet(newRead,i+5);
      }
    }
    if (oldRead == newRead) {
        tempo--;
    } else {
        tempo = 4;
        oldRead = newRead;
    }
    if (tempo == 0) {
        keys = oldRead;
    }
}
void kpInit(void) {
  soInit();
  pinMode(KEYPAD_1_PIN, INPUT);
  pinMode(KEYPAD_2_PIN, INPUT);
}
