#include "Led.h"
#include <LPC21xx.H>

#define LED0_bm (1 << 16)
#define LED1_bm (1 << 17)
#define LED2_bm (1 << 18)
#define LED3_bm (1 << 19)

enum Direction 
{
	LEFT,
	RIGHT
};

void Delay(unsigned int uiTimer) ///funkcja delay z argumentem (w milisekundach)
{
	unsigned int uiLoopCounter;
	for (uiLoopCounter = 0; uiLoopCounter < uiTimer * 12000; uiLoopCounter++){}
}


void LedInit() ///ustawia 4 diody w gotowosci, a zerowa zapala
{
	IO1DIR = (LED0_bm | LED1_bm | LED2_bm | LED3_bm) | IO1DIR; 
	IO1SET = LED0_bm;
}

void LedOn(unsigned int uiDiodeNr) ///jako argumnt podaje sie nr diody ktora ma zostac zapalona
{
	IO1CLR = (LED0_bm | LED1_bm | LED2_bm | LED3_bm) | IO1CLR;
	
	switch(uiDiodeNr)
	{
		case 0:
			IO1SET = LED0_bm;
			break;
		case 1:
			IO1SET = LED1_bm;
			break;
		case 2:
			IO1SET = LED2_bm;
			break;
		case 3:
			IO1SET = LED3_bm;
			break;
		default:
			break;
	}
}

void LedStep(enum Direction eWhichDirection) ///poczawszy od diody 0 zapala kolejne w damnym kiernku
{
	static unsigned int uiStepPosition;
	
	if(eWhichDirection == LEFT)
		uiStepPosition = (uiStepPosition + 1) % 4;
	else 
		uiStepPosition = (uiStepPosition - 1) % 4;
	LedOn(uiStepPosition);
}

void LedStepLeft()
{
	LedStep(LEFT);
}

void LedStepRight()
{
	LedStep(RIGHT);
}