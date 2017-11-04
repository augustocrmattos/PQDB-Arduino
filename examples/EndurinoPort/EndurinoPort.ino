//#define CHIPKIT

#include "ad.h"
#include "lcd.h"
#include "keypad.h"
#include "pwm.h"
#include "rgb.h"
//#include "serial.h"
#include "so.h"
#include "ssd.h"
#include "timer.h"
#include "i2c.h"
#include "ds1307.h"

char tela[4][16], linha = 0, coluna = 11, flagob = 0,  randomico = 0;
char apagaverde = 0;
int cont = 0, pontos = 0;
int last_lcd_key = 5;
int lcd_key     = 5;
int adc_key_in  = 0;
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   10
#define btnSTART  9
#define btnA      7
#define btnX      8
#define btnY      5
#define btnB      6

#define NOTE_E7  2637

#define NOTE_C7  2093

#define c1 1
#define c2 2
#define b1 3
#define b2 4
#define cb1 5
#define cb2 6
#define p1 7

#define bomba 20

byte carro1[8] = {
  0b01010,
  0b11111,
  0b11111,
  0b01010,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};
byte carro2[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b01010,
  0b11111,
  0b11111,
  0b01010
};
byte barra1[8] = {
  0b11111,
  0b10001,
  0b10001,
  0b11111,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};
byte barra2[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b11111,
  0b10001,
  0b10001,
  0b11111
};
byte carrobarra1[8] = {
  0b01010,
  0b11111,
  0b11111,
  0b01010,
  0b11111,
  0b10001,
  0b10001,
  0b11111
};
byte carrobarra2[8] = {
  0b11111,
  0b10001,
  0b10001,
  0b11111,
  0b01010,
  0b11111,
  0b11111,
  0b01010
};
byte pista[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};

#define buzzerpositive 19
#define buzzerdata 20
#define buzzerlow 21
#define red1 29
#define red2 37
#define red3 45
#define green1 25
#define green2 33
#define green3 41
#define green4 49

void imprime() {
  int i, j, k = 3, conta = 0, linhaimprime = linha, flag = 0;
  lcdCommand(0x80);

  for (j = 0; j < 16; j++) {
    if (linha == 0 && coluna == j) {
      if (tela[1][j] == 0)     {
        lcdChar((byte)c1);
        continue;
      }
      if (tela[1][j] == bomba) {
        lcdChar((byte)cb1);
        continue;
      }
    }
    if (tela[0][j] == bomba) {
      if (linha == 1 && coluna == j) {
        lcdChar((byte)cb2);
        continue;
      }
      if (tela[1][j] == 0)       {
        lcdChar((byte)b1);
        continue;
      }
    }
    if (tela[0][j] == 0) {
      if (linha == 1 && coluna == j) {
        lcdChar((byte)c2);
        continue;
      }
      if (tela[1][j] == 0)       {
        lcdChar((byte)p1);
        continue;
      }
      if (tela[1][j] == bomba)   {
        lcdChar((byte)b2);
        continue;
      }
    }
  }
  lcdCommand(0xC0);
  linhaimprime++;
  for (j = 0; j < 16; j++) {
    if (linha == 2 && coluna == j) {
      if (tela[3][j] == 0)       {
        lcdChar((byte)c1);
        continue;
      }
      if (tela[3][j] == bomba)   {
        lcdChar((byte)cb1);
        continue;
      }
    }
    if (tela[2][j] == bomba) {
      if (linha == 3 && coluna == j) {
        lcdChar((byte)cb2);
        continue;
      }
      if (tela[3][j] == 0)       {
        lcdChar((byte)b1);
        continue;
      }
    }
    if (tela[2][j] == 0) {
      if (linha == 3 && coluna == j) {
        lcdChar((byte)c2);
        continue;
      }
      if (tela[3][j] == 0)       {
        lcdChar((byte)p1);
        continue;
      }
      if (tela[3][j] == bomba)   {
        lcdChar((byte)b2);
        continue;
      }
    }
  }
  /*
    lcdCommand(0x80);
    lcdString("PTOS|");
    lcdCommand(0xC0);
    lcdCommand(0xC0);
    if (pontos < 99) lcdString(" ");
    //lcd.print(pontos);
    lcdChar((char)((pontos / 100) % 10) + 48);
    lcdChar((char)((pontos / 10) % 10) + 48);
    lcdChar((char)(pontos % 10) + 48);
    lcdString("|");
  */
}

int freeforall = 0, ffa = 0;
int read_LCD_buttons()
{
  int button = kpRead();
  if (button == freeforall) {
    ffa++;
  }
  else {
    freeforall = button;
  }
  if (ffa == 2) {
    ffa = 0;
    return button;
  }
  return 0;
}


void leBotoes() {
  //pegar apenas o pressionamento
  if (lcd_key == kpReadKey()) {
    return;
  }
  lcd_key = kpReadKey();
  switch (lcd_key) {
    case 'U'://btnUP:
      {
        if (linha > 0) linha--;
        break;
      }
    case 'D'://btnDOWN:
      {
        if (linha < 3) linha++;
        break;
      }
    case 'R'://btnRIGHT:
      {
        if (coluna < 15) coluna++;
        break;
      }
    case 'L'://btnLEFT:
      {
        if (coluna > 5) coluna--;
        break;
      }
  }
}

void mover() {
  int i, j, r1, r2;
  //  lcd.setCursor(0,0);
  //  lcd.write("ok");
  for (i = 0; i < 4; i++) {
    for (j = 15; j > 0; j--) {
      tela[i][j] = tela[i][j - 1];
    }
  }
  tela[0][0] = 0;
  tela[1][0] = 0;
  tela[2][0] = 0;
  tela[3][0] = 0;
  if (flagob >= 2) {
    r1 = (randomico + rand()) % 3;
    r2 = (randomico + rand()) % 4;
    if (!r1) tela[r2][0] = bomba;
    flagob = 0;
  }
  else flagob++;
  lcdCommand(0x80);
}


void ptos() {
  //checa se ultrapassou alguma bomba
  for (char generico = 0; generico < 4; generico++) {
    if (tela[generico][coluna] == 20)
    {
      pontos++;
      //ssdDigit(0, 0);
      //ssdDigit(1, 0);
      ssdDigit(2, (pontos / 10) % 10);
      ssdDigit(3, (pontos) % 10);
    }
  }
}
void waitStart(){

  char leitura = kpReadKey();

  while(leitura !='S'){

    leitura = kpReadKey();
    Serial.println(leitura);
    kpDebounce();
  }
}
void inicializa() {
  int i, j;
  linha = 1; coluna = 12;
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 16; j++) {
      tela[i][j] = 0;
      if (j == 3 && i == 0) tela[i][j] = bomba;
      if (j == 9 && i == 2) tela[i][j] = bomba;
    }
  }
}

void condicaoDerrota() {
  int flagasterisco = 0;
  if (tela[linha][coluna] == bomba) {
    randomico = 0;
    //lcd.clear();
    lcdCommand(0x80);
    lcdString(" Voce   Perdeu! ");
    lcdCommand(0xC0);
    lcdString("PTOS:");
    lcdChar((char)((pontos / 100) % 10) + 48);
    lcdChar((char)((pontos / 10) % 10) + 48);
    lcdChar((char)(pontos % 10) + 48);
    
    pontos = 0;
    lcdCommand(0xC8);
    lcdString(" aperte start ");
    waitStart();
    
    cont++;
    
  }
}

void setup() {

  Serial.begin(115200);
  adInit();
  lcdInit();
  kpInit();
  pwmInit();
  rgbInit();
  dsInit();
  //serialInit();
  soInit();
  ssdInit();
  timerInit();
  ssdDigit(0, 0);
  ssdDigit(1, 0);
  ssdDigit(2, 0);
  ssdDigit(3, 0);
  lcdCreateChar(1, carro1);
  lcdCreateChar(2, carro2);
  lcdCreateChar(3, barra1);
  lcdCreateChar(4, barra2);
  lcdCreateChar(5, carrobarra1);
  lcdCreateChar(6, carrobarra2);
  lcdCreateChar(7, pista);

  Serial.println("comecou");
  inicializa();
  imprime();
  lcdCommand(0x80);
  lcdString("Pressione");
  lcdCommand(0xC0);
  lcdString("Start");
  waitStart();
}


int adcSpeed;
void loop() {

  //le e transforma de 1 à 11
  adcSpeed = (adRead(2)>>6)+1;  
  ssdDigit(0, ((11-adcSpeed)/10)%10);
  ssdDigit(1, (11-adcSpeed)%10);

    if (cont % adcSpeed == 0) mover();
    if (cont % adcSpeed == 0) imprime();
    if (cont % adcSpeed == 0) condicaoDerrota();
    if (cont % adcSpeed == 0) ptos();

    for (int i = 0; i < 12; i++) {
      kpDebounce();
      ssdUpdate();
      timerDelay(3);
    }
    leBotoes();
    cont++;
    kpReadKey();
}
