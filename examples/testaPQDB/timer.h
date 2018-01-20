#ifndef TIMER_H
	#define TIMER_H
	void timerStart(unsigned int count_val);
	void timerWait(void);
	int timerFinished(void);
	void timerDelay(unsigned int time);
	void timerInit(void);
#endif