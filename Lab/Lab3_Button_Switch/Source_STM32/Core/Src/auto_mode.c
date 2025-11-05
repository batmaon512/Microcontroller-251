/*
 * auto_mode.c
 *
 *  Created on: Nov 4, 2025
 *      Author: chith
 */
#include "auto_mode.h"

void auto_mode(void){
if(mode != 0) return;
if(flagPress[0] == 1){
	mode = 1;
	flagPress[0] = 0;
	counter_trafic_light = 0;
	counter_7LED = 0;
	TempConfigure = TIME_RED_LED;
	  HAL_GPIO_WritePin(LED_RED0_GPIO_Port, LED_RED0_Pin, 1);
	  HAL_GPIO_WritePin(LED_GREEN0_GPIO_Port, LED_GREEN0_Pin, 1);
	  HAL_GPIO_WritePin(LED_AMBER0_GPIO_Port, LED_AMBER0_Pin, 1);
	  HAL_GPIO_WritePin(LED_RED1_GPIO_Port, LED_RED1_Pin, 1);
	  HAL_GPIO_WritePin(LED_GREEN1_GPIO_Port, LED_GREEN1_Pin, 1);
	  HAL_GPIO_WritePin(LED_AMBER1_GPIO_Port, LED_AMBER1_Pin, 1);
	return;
}
if(flagPress[1] == 1 || flagPress[2] == 1){flagPress[1] = 0; flagPress[2] = 0;}
if(flagLongPress[0] == 1 || flagLongPress[1] == 1 || flagLongPress[2] == 1){
	flagLongPress[0] = 0; flagLongPress[1] = 0; flagLongPress[2] = 0;
}
if(TIME_RED_LED < 2000/TRAFIC_SCAN){
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
