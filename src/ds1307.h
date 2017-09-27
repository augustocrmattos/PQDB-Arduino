/*
 * DS1307RTC.h - library for DS1307 RTC
 * This library is intended to be uses with Arduino Time.h library functions
 */

#ifndef DS1307RTC_h
#define DS1307RTC_h

void dsInit(void);
void dsStartClock(void);
void dsStopClock(void);

#define SEC     0
#define MIN     1
#define HOUR    2
#define WEEKDAY 3
#define DAY     4
#define MONTH   5
#define YEAR    6

int dec2bcd(int value);
int bcd2dec(int value);
void dsWrite(unsigned char value, int address);
int dsRead(int address);

//Macros para ler os valores já convertidos
#define getSeconds() (bcd2dec(dsRead(SEC)  & 0x7f))
#define getMinutes() (bcd2dec(dsRead(MIN)  & 0x7f))
#define getHours()   (bcd2dec(dsRead(HOUR) & 0x5f))
#define getDays()    (bcd2dec(dsRead(DAY)  & 0x5f))
#define getMonths()  (bcd2dec(dsRead(MONTH)& 0x3f))
#define getYears()   (bcd2dec(dsRead(YEAR) & 0xff))


#endif
 

