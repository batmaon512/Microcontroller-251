/*
 * configure_mode.c
 *
 *  Created on: Nov 4, 2025
 *      Author: chith
 */

#include "configure_mode.h"
#define TIME_COUNT_IN_LONG_PRESS 100
int counter_long_press = 0;

void configure_mode(void){
	if(mode == 0) return;
	switch(mode){
	case 1:
		if(flagPress[0] == 1){
			flagPress[0] = 0;
			mode = 2;
			TempConfigure = TIME_AMBER_LED;
			counter_long_press = 0;
			  HAL_GPIO_WritePin(LED_RED0_GPIO_Port, LED_RED0_Pin, 1);
			  HAL_GPIO_WritePin(LED_GREEN0_GPIO_Port, LED_GREEN0_Pin, 1);
			  HAL_GPIO_WritePin(LED_AMBER0_GPIO_Port, LED_AMBER0_Pin, 1);
			  HAL_GPIO_WritePin(LED_RED1_GPIO_Port, LED_RED1_Pin, 1);
			  HAL_GPIO_WritePin(LED_GREEN1_GPIO_Port, LED_GREEN1_Pin, 1);
			  HAL_GPIO_WritePin(LED_AMBER1_GPIO_Port, LED_AMBER1_Pin, 1);
			return;
		}
		if(flagPress[2] == 1){
			flagPress[2] = 0;
			mode = 0;
			TIME_RED_LED = TempConfigure;
			return;
		}
		if(counter_configure_mode >= 250/TIME_SCAN){
			counter_configure_mode = 0;
			HAL_GPIO_TogglePin(LED_RED0_GPIO_Port, LED_RED0_Pin);
			HAL_GPIO_TogglePin(LED_RED1_GPIO_Port, LED_RED1_Pin);
			led_buffer[2] = 0;
			led_buffer[3] = mode;
			int temp = TempConfigure*TRAFIC_SCAN/1000;
			led_buffer[0] = temp/10;
			led_buffer[1] = temp%10;
		}
		break;
	case 2:
		if(flagPress[0] == 1){
			flagPress[0] = 0;
			mode = 3;
			TempConfigure = TIME_GREEN_LED;
			counter_long_press = 0;
			  HAL_GPIO_WritePin(LED_RED0_GPIO_Port, LED_RED0_Pin, 1);
			  HAL_GPIO_WritePin(LED_GREEN0_GPIO_Port, LED_GREEN0_Pin, 1);
			  HAL_GPIO_WritePin(LED_AMBER0_GPIO_Port, LED_AMBER0_Pin, 1);
			  HAL_GPIO_WritePin(LED_RED1_GPIO_Port, LED_RED1_Pin, 1);
			  HAL_GPIO_WritePin(LED_GREEN1_GPIO_Port, LED_GREEN1_Pin, 1);
			  HAL_GPIO_WritePin(LED_AMBER1_GPIO_Port, LED_AMBER1_Pin, 1);
			return;
		}
		if(flagPress[2] == 1){
			flagPress[2] = 0;
			TIME_AMBER_LED = TempConfigure;
			mode = 0;
			return;
		}
		if(counter_configure_mode >= 250/TIME_SCAN){
			counter_configure_mode = 0;
			HAL_GPIO_TogglePin(LED_AMBER0_GPIO_Port, LED_AMBER0_Pin);
			HAL_GPIO_TogglePin(LED_AMBER1_GPIO_Port, LED_AMBER1_Pin);
			led_buffer[2] = 0;
			led_buffer[3] = mode;
			int temp = TempConfigure*TRAFIC_SCAN/1000;
			led_buffer[0] = temp/10;
			led_buffer[1] = temp%10;
		}
		break;
	case 3:
		if(flagPress[0] == 1){
			flagPress[0] = 0;
			mode = 0;
			return;
		}
		if(flagPress[2] == 1){
			flagPress[2] = 0;
			mode = 0;
			TIME_GREEN_LED = TempConfigure;
			counter_long_press = 0;
			counter_trafic_light = 0;
			return;
		}
		if(counter_configure_mode >= 250/TIME_SCAN){
			counter_configure_mode = 0;
			HAL_GPIO_TogglePin(LED_GREEN0_GPIO_Port, LED_GREEN0_Pin);
			HAL_GPIO_TogglePin(LED_GREEN1_GPIO_Port, LED_GREEN1_Pin);
			led_buffer[2] = 0;
			led_buffer[3] = mode;
			int temp = TempConfigure*TRAFIC_SCAN/1000;
			led_buffer[0] = temp/10;
			led_buffer[1] = temp%10;
		}
		break;
	}
	if(flagPress[1] == 1){
		flagPress[1] = 0;
		TempConfigure += 1000/TRAFIC_SCAN;
		if(TempConfigure > 99000/TRAFIC_SCAN) TempConfigure = 1000/TRAFIC_SCAN;
	}
	if(flagLongPress[1] == 1){
		flagLongPress[1] = 0;
		if(counter_long_press >= TIME_COUNT_IN_LONG_PRESS /TIME_SCAN){
			TempConfigure += 1000/TRAFIC_SCAN;
			if(TempConfigure > 99000/TRAFIC_SCAN) TempConfigure = 1000/TRAFIC_SCAN;
			counter_long_press = 0;
		}
		else counter_long_press++;
	}
	counter_configure_mode++;
}
