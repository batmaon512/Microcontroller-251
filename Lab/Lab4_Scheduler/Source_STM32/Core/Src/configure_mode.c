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
		if(event_button_long(0) == 1){
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
		if(event_button(2) == 1){
			TIME_RED_LED = TempConfigure;
			return;
		}
		if(counter_configure_mode >= 250/TIME_SCAN){
			counter_configure_mode = 0;
			HAL_GPIO_TogglePin(LED_RED0_GPIO_Port, LED_RED0_Pin);
			HAL_GPIO_TogglePin(LED_RED1_GPIO_Port, LED_RED1_Pin);
		}
		break;
	case 2:
		if(event_button_long(0) == 1){
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
		if(event_button(2) == 1){
			TIME_AMBER_LED = TempConfigure;
			return;
		}
		if(counter_configure_mode >= 250/TIME_SCAN){
			counter_configure_mode = 0;
			HAL_GPIO_TogglePin(LED_AMBER0_GPIO_Port, LED_AMBER0_Pin);
			HAL_GPIO_TogglePin(LED_AMBER1_GPIO_Port, LED_AMBER1_Pin);
		}
		break;
	case 3:
		if(event_button_long(0) == 1){
			mode = 0;
			return;
		}
		if(event_button(2) == 1){
			TIME_GREEN_LED = TempConfigure;
			counter_long_press = 0;
			counter_trafic_light = 0;
			return;
		}
		if(counter_configure_mode >= 250/TIME_SCAN){
			counter_configure_mode = 0;
			HAL_GPIO_TogglePin(LED_GREEN0_GPIO_Port, LED_GREEN0_Pin);
			HAL_GPIO_TogglePin(LED_GREEN1_GPIO_Port, LED_GREEN1_Pin);
		}
		break;
	}
	led_buffer[2] = 0;
	led_buffer[3] = mode;
	int temp = TempConfigure*TRAFIC_SCAN/1000;
	led_buffer[0] = temp/10;
	led_buffer[1] = temp%10;

	if(event_button(0) == 1){
		TempConfigure -= 1000/TRAFIC_SCAN;
		if(TempConfigure <= 0) TempConfigure = 99000/TRAFIC_SCAN;
	}

	if(event_button(1) == 1){
		TempConfigure += 1000/TRAFIC_SCAN;
		if(TempConfigure > 99000/TRAFIC_SCAN) TempConfigure = 1000/TRAFIC_SCAN;
	}

	if(is_button_long_pressed(1) == 1){
		if(counter_long_press >= TIME_COUNT_IN_LONG_PRESS /TIME_SCAN){
			TempConfigure += 1000/TRAFIC_SCAN;
			if(TempConfigure > 99000/TRAFIC_SCAN) TempConfigure = 1000/TRAFIC_SCAN;
			counter_long_press = 0;
		}
		else counter_long_press++;
	}
	counter_configure_mode++;
}
