#include "keypad.h"
#include "so.h"
#include "io.h"

static unsigned int keys;

unsigned int kpRead(void) {
    return keys;
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
