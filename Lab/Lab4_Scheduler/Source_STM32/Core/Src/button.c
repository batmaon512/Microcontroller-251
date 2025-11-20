/*
 * button.c
 *
 *  Created on: Oct 28, 2025
 *      Author: chith
 */

#include "button.h"
//CONFIG PIN, PORT FOR BUTTON
static uint16_t BUTTON_MAP[MAX_BUTTONS] = {BUTTON0_Pin, BUTTON1_Pin, BUTTON2_Pin};
static GPIO_TypeDef* BUTTON_PORT_MAP[MAX_BUTTONS] = {BUTTON0_GPIO_Port, BUTTON1_GPIO_Port, BUTTON2_GPIO_Port};
//
static GPIO_PinState buttonBuffer[MAX_BUTTONS];
static GPIO_PinState debounceButtonBuffer[MAX_BUTTONS];
static uint16_t counterButtonBuffer[MAX_BUTTONS] = {0};
static uint16_t counterButtonLongPress[MAX_BUTTONS] = {0};
//
static uint8_t eventPress[MAX_BUTTONS] = {0};
static uint8_t flagButtonLongPress[MAX_BUTTONS] = {0};
static uint8_t eventTransitionLongPress[MAX_BUTTONS] = {0};
void init_button(){
	for(int i = 0; i < MAX_BUTTONS; i++){
		buttonBuffer[i] = GPIO_PIN_SET;
		debounceButtonBuffer[i] = GPIO_PIN_SET;
	}
}

void button_reading(void){
	for(int i = 0; i < MAX_BUTTONS; i++){
		GPIO_PinState temp = HAL_GPIO_ReadPin(BUTTON_PORT_MAP[i], BUTTON_MAP[i]);
		if(debounceButtonBuffer[i] != temp){
			counterButtonBuffer[i] = 0;
			debounceButtonBuffer[i] = temp;
		}
		else if(buttonBuffer[i] != temp){
			if(counterButtonBuffer[i] < TIME_BOUNCING) counterButtonBuffer[i] += TIME_BUTTON_SCAN;
			else{
				buttonBuffer[i] = temp;
				if(temp == BUTTON_IS_PRESSED){
					eventPress[i]++;
				}
				else{
					flagButtonLongPress[i] = 0;
					counterButtonLongPress[i] = 0;
				}
			}
		}
		else if(buttonBuffer[i] == BUTTON_IS_PRESSED){
			if(counterButtonLongPress[i] < TIME_LONG_PRESS) counterButtonLongPress[i] += TIME_BUTTON_SCAN;
			else if(flagButtonLongPress[i] == 0){
				eventTransitionLongPress[i]++;
				flagButtonLongPress[i] = 1;
			}
		}
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
unsigned char event_button(int index){
	if(index >= MAX_BUTTONS) return 0;
	if(eventPress[index] <= 0) return 0;
	eventPress[index]--;
	return 1;
}
unsigned char event_button_long(int index){
	if(index >= MAX_BUTTONS) return 0;
	if(eventTransitionLongPress[index] <= 0) return 0;
	eventTransitionLongPress[index]--;
	return 1;
}
void clear_event_button(int index){
	if(index >= MAX_BUTTONS) return;
	eventPress[index] = 0;
	return;
}
void clear_event_button_long(int index){
	if(index >= MAX_BUTTONS) return;
	eventTransitionLongPress[index] = 0;
	return;
}
