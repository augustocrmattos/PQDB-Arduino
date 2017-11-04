#ifndef LCD
  #define LCD
  #include <Arduino.h>
  void lcdCommand(char value);
  void lcdChar(char value);
  void lcdString(char msg[]);
  void lcdCreateChar(int pos, byte line[]);
  void lcdInit ();
#endif
