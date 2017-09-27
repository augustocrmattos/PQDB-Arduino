#include "lcd.h"

#define LCD_COLS 16
#define LCD_LINES 2
#define BUFF_LINES 4

//mais um pra guardar o '\0' no fim de cada linha
#define BUFF_COLS (LCD_COLS+1)

char buffer[BUFF_LINES][BUFF_COLS];
int line;
int col;

void consoleInit() {
	int i, j;
	lcdInit();
	for (i = 0; i < BUFF_LINES; i++) {
		for (j = 0; j < BUFF_COLS; j++) {
			buffer[i][j] = '\0';
		}
	}
	line = (BUFF_LINES - LCD_LINES);
	col = 0;
}

void newLine(void) {
	int l;
	int c ;
	//sobe cada linha do buffer em uma posição
	for (l = 1; l < BUFF_LINES; l++) {
		for (c = 0; c < BUFF_COLS; c++) {
			buffer[l - 1][c] = buffer[l][c];
		}
	}
	//limpa a última linha
	for (l = 0; l < BUFF_COLS; l++) {
		buffer[BUFF_LINES - 1][l] = '\0';
	}
}

void consoleUpdate(void) {
	int i, j;
	lcdCommand(0x01);
	for (i = 0; i < LCD_LINES; i++) {
		lcdPosition(i,0);
		for (j = 0; j < BUFF_COLS; j++) {
			if ((buffer[line + i][j] == '\0')) {
				break;
			} else {
				lcdChar(buffer[line + i][j]);
			}
		}
	}
}

void consolePrint(char* vet) {
	char i, j;
	int currentPos = 0;
	//enquanto a string não terminar continua processando
	while (vet[currentPos] != '\0') {
		//se chegou uma nova linha termina a atual e passa pra próxima
		if (vet[currentPos] == '\n') {
			buffer[BUFF_LINES - 1][col] = '\0';
			col = 0;
			newLine();
		} else {
			//se chegou uma letra normal armazena no buffer
			buffer[BUFF_LINES - 1][col] = vet[currentPos];
			col++;
			//se encheu a linha, passa para próxima
			//(-1 por causa do espaço para o '\0')
			if (col >= (BUFF_COLS - 1)) {
				buffer[BUFF_LINES - 1][BUFF_COLS - 1] = '\0';
				col = 0;
				newLine();
			}
		}
		currentPos++;
	}
	//armazena '\0' na última posição
	buffer[BUFF_LINES - 1][col] = vet[currentPos];
}

//muda a posição da linha que deve ser exibida
void consoleMoveLine(int relativeMove) {
	if (relativeMove < 0) {
		if (line > 0) {
			line--;
		}
	}
	if (relativeMove > 0) {
		if (line < BUFF_LINES - LCD_LINES) {
			line++;
		}
	}
}
