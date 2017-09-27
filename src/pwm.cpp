#include "pwm.h"
#include "io.h"

void pwmBuzzer(unsigned int frequency){
  if ((frequency>31) && (frequency < 4000)){
    tone(PWM_PIN,frequency);
  }else{
    noTone(PWM_PIN);
  }
}
void pwmInit(void){
  pinMode(PWM_PIN,OUTPUT);
  digitalWrite(PWM_PIN,LOW);
}

