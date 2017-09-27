#include "timer.h"
#include "arduino.h"

//guarda o tempo final da contagem
unsigned long int targetTime;

//configura tempo
void timerStart(unsigned int time){
	targetTime = millis() + time;
}
//aguarda fim da contagem
void timerWait(void){
	while(targetTime > millis());
}
//verifica se a contagem já terminou
int timerFinished(void){
	if (targetTime > millis()){
		return 0;
	}else{
		return 1;
	}
}
//gera um atraso de (time) milissegundos
void timerDelay(unsigned int time){
	timerStart(time);
	timerWait();
}

void timerInit(void){
	//não precisa fazer nada, o arduino já inicializa o timer	
}
