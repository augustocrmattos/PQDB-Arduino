#ifndef RGB
  #define RGB
  
  #define RED    1
  #define GREEN  2
  #define BLUE   4
  #define YELLOW 3
  #define CYAN   6
  #define PURPLE 5   
  #define WHITE  7
void rgbColor(int led);
void turnOff(int led);
void turnOn(int led);
void rgbInit(void);
  
#endif
