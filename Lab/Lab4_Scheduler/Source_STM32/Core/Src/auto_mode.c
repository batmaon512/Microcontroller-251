/*
 * auto_mode.c
 *
 *  Created on: Nov 4, 2025
 *      Author: chith
 */
#include "auto_mode.h"

void auto_mode(void){
if(mode != 0) return;
if(event_button_long(0) == 1){
	mode = 1;
	counter_trafic_light = 0;
	counter_7LED = 0;
	TempConfigure = TIME_RED_LED;
	  HAL_GPIO_WritePin(LED_RED0_GPIO_Port, LED_RED0_Pin, 1);
	  HAL_GPIO_WritePin(LED_GREEN0_GPIO_Port, LED_GREEN0_Pin, 1);
	  HAL_GPIO_WritePin(LED_AMBER0_GPIO_Port, LED_AMBER0_Pin, 1);
	  HAL_GPIO_WritePin(LED_RED1_GPIO_Port, LED_RED1_Pin, 1);
	  HAL_GPIO_WritePin(LED_GREEN1_GPIO_Port, LED_GREEN1_Pin, 1);
	  HAL_GPIO_WritePin(LED_AMBER1_GPIO_Port, LED_AMBER1_Pin, 1);
	 clear_event_button(0);
	 clear_event_button(1);
	 clear_event_button(2);
	 clear_event_button_long(1);
	 clear_event_button_long(2);
	return;
}
if(TIME_RED_LED <= TIME_AMBER_LED){
	  HAL_GPIO_TogglePin(LED_RED0_GPIO_Port, LED_RED0_Pin);
	  HAL_GPIO_TogglePin(LED_GREEN0_GPIO_Port, LED_GREEN0_Pin);
	  HAL_GPIO_TogglePin(LED_AMBER0_GPIO_Port, LED_AMBER0_Pin);
	  HAL_GPIO_TogglePin(LED_RED1_GPIO_Port, LED_RED1_Pin);
	  HAL_GPIO_TogglePin(LED_GREEN1_GPIO_Port, LED_GREEN1_Pin);
	  HAL_GPIO_TogglePin(LED_AMBER1_GPIO_Port, LED_AMBER1_Pin);
	  return;
}
trafic_light();
}
