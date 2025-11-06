/*
 * button.c
 *
 *  Created on: Oct 28, 2025
 *      Author: chith
 */

#include "button.h"



void button_reading(void){
	for(int i = 0; i < MAX_BUTTONS; i++){
		GPIO_PinState temp = HAL_GPIO_ReadPin(BUTTON_PORT_MAP[i], BUTTON_MAP[i]);
		if(debounceButtonBuffer[i] != temp) counterButtonBuffer[i] = 0;
		else{
			if(counterButtonBuffer[i] < TIME_BOUNCING) counterButtonBuffer[i] += TIME_BUTTON_SCAN;
			else{
				if(buttonBuffer[i] == temp && temp == BUTTON_IS_RELEASED) continue;
				buttonBuffer[i] = temp;
				if(buttonBuffer[i] == BUTTON_IS_RELEASED){
					flagButtonLongPress[i] = 0;
					counterButtonLongPress[i] = 0;
				}
				else{
					if(counterButtonLongPress[i] < TIME_OUT_LONG_PRESS) counterButtonLongPress[i] += TIME_BUTTON_SCAN;
					else flagButtonLongPress[i] = 1;
					}
				}
			}
		debounceButtonBuffer[i] = temp;
	}
}


unsigned char is_button_pressed(int index){
	if(index >= MAX_BUTTONS) return 0;
	return (buttonBuffer[index] == BUTTON_IS_PRESSED);
}

unsigned char is_button_long_pressed(int index){
	if(index >= MAX_BUTTONS) return 0xff;
	return (flagButtonLongPress[index] == 1);
}

void fsm_button(void){
	for(int i = 0; i < MAX_BUTTONS; i++){
		switch (buttonState[i]) {
		        case BUTTON_RELEASED:
		            if (is_button_pressed(i)) {
		                buttonState[i] = BUTTON_PRESSED;
		                flagPress[i] = 1;
		            }
		            break;
		        case BUTTON_PRESSED:
		            if (!is_button_pressed(i)) buttonState[i] = BUTTON_RELEASED;
		            else if (is_button_long_pressed(i)){
		            	flagTransitionLongPress[i] = 1;
		            	buttonState[i] = BUTTON_LONG_PRESSED;}
		            break;
		        case BUTTON_LONG_PRESSED:
		            if (!is_button_pressed(i)) buttonState[i] = BUTTON_RELEASED;
		            flagLongPress[i] = 1;
		            break;
		    }

	}
}

