#include <stdlib.h>
#include <stdio.h>
#include "myLib.h"
#define DEBUG

void fillScreen(volatile unsigned short color); 
volatile unsigned short bgcolor = WHITE; 

int main()
{

	int key_up_pressed;
	int key_down_pressed;
	int key_left_pressed;
	int key_right_pressed; 
	REG_DISPCTL = MODE3 | BG2_ENABLE;
	enum GameState gstate = START; 
	
	switch (gstate) {
		case START:
			break; 
		case START_NODRAW:
			break; 
		case PLAY:
			Spacecraft procraft; 
			procraft.xpos = 37; 
			procraft.ypos = 21;
			procraft.width = 5; 
			procraft.height = 5; 
			procraft.color = RED; 
	
			while(1) {
				waitForVBlank(); 
				if (KEY_DOWN_NOW(BUTTON_UP)) { 
					procraft.ypos -= 1;
					displaySpacecraft(procraft);
				} else if(KEY_DOWN_NOW(BUTTON_DOWN)) {
					procraft.ypos += 1;
					displaySpacecraft(procraft);
				} else if(KEY_DOWN_NOW(BUTTON_LEFT)) {
					procraft.xpos -= 1;
					displaySpacecraft(procraft);
				} else if(KEY_DOWN_NOW(BUTTON_RIGHT)) {
					procraft.xpos += 1;
					displaySpacecraft(procraft);
				}
		
	}
		case PLAY_NODRAW:
			break; 
		case PAUSE:
			break; 
		case PAUSE_NODRAW:
			break; 
	}
	return 0;
}

void displaySpacecraft(Spacecraft craft)
{
	int xpos = craft.xpos;
	int ypos = craft.ypos;
	int width = craft.width; 
	volatile unsigned short color = craft.color; 
 
	REG_DMA3SAD = (int) &bgcolor;
  	REG_DMA3DAD = (int) videoBuffer;
  	REG_DMA3CNT = 38400 | DMA_ON | DMA_SOURCE_FIXED;

	REG_DMA3SAD = (int) &color;
  	REG_DMA3DAD = (int) (&videoBuffer[OFFSET(ypos, xpos, 240)]);
  	REG_DMA3CNT =  width | DMA_ON | DMA_SOURCE_FIXED;
}

void fillScreen(volatile unsigned short color) {
	REG_DMA3SAD = (int) &color;
  	REG_DMA3DAD = (int) videoBuffer;
  	REG_DMA3CNT = 38400 | DMA_ON | DMA_SOURCE_FIXED;
}

void waitForVBlank()
{
	while(SCANLINECOUNTER > 160);
	while(SCANLINECOUNTER < 160);
}
