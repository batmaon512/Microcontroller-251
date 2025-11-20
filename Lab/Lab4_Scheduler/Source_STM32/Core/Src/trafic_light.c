/*
 * trafic_light.c
 *
 *  Created on: Nov 3, 2025
 *      Author: chith
 */
#include "trafic_light.h"

void trafic_light(){
//CONTROL LED TRAFFIC
		  if(counter_trafic_light == 0){
			  HAL_GPIO_WritePin(LED_RED0_GPIO_Port, LED_RED0_Pin, 0);
			  HAL_GPIO_WritePin(LED_GREEN0_GPIO_Port, LED_GREEN0_Pin, 1);
			  HAL_GPIO_WritePin(LED_AMBER0_GPIO_Port, LED_AMBER0_Pin, 1);
			  HAL_GPIO_WritePin(LED_RED1_GPIO_Port, LED_RED1_Pin, 1);
			  HAL_GPIO_WritePin(LED_GREEN1_GPIO_Port, LED_GREEN1_Pin, 0);
			  HAL_GPIO_WritePin(LED_AMBER1_GPIO_Port, LED_AMBER1_Pin, 1);
		  	  state_trafic_light = 0;
		  	  }
		  else if(counter_trafic_light == TIME_RED_LED - TIME_AMBER_LED){
			  HAL_GPIO_WritePin(LED_RED0_GPIO_Port, LED_RED0_Pin, 0);
			  HAL_GPIO_WritePin(LED_GREEN0_GPIO_Port, LED_GREEN0_Pin, 1);
			  HAL_GPIO_WritePin(LED_AMBER0_GPIO_Port, LED_AMBER0_Pin, 1);
			  HAL_GPIO_WritePin(LED_RED1_GPIO_Port, LED_RED1_Pin, 1);
			  HAL_GPIO_WritePin(LED_GREEN1_GPIO_Port, LED_GREEN1_Pin, 1);
			  HAL_GPIO_WritePin(LED_AMBER1_GPIO_Port, LED_AMBER1_Pin, 0);
	  	  	  state_trafic_light = 1;
		  }
		  else if(counter_trafic_light == TIME_RED_LED){
			  HAL_GPIO_WritePin(LED_RED0_GPIO_Port, LED_RED0_Pin, 1);
			  HAL_GPIO_WritePin(LED_GREEN0_GPIO_Port, LED_GREEN0_Pin, 0);
			  HAL_GPIO_WritePin(LED_AMBER0_GPIO_Port, LED_AMBER0_Pin, 1);
			  HAL_GPIO_WritePin(LED_RED1_GPIO_Port, LED_RED1_Pin, 0);
			  HAL_GPIO_WritePin(LED_GREEN1_GPIO_Port, LED_GREEN1_Pin, 1);
			  HAL_GPIO_WritePin(LED_AMBER1_GPIO_Port, LED_AMBER1_Pin, 1);
			  state_trafic_light = 2;
		  	  }
		  else if(counter_trafic_light == TIME_RED_LED + TIME_GREEN_LED){
			  HAL_GPIO_WritePin(LED_RED0_GPIO_Port, LED_RED0_Pin, 1);
			  HAL_GPIO_WritePin(LED_GREEN0_GPIO_Port, LED_GREEN0_Pin, 1);
			  HAL_GPIO_WritePin(LED_AMBER0_GPIO_Port, LED_AMBER0_Pin, 0);
			  HAL_GPIO_WritePin(LED_RED1_GPIO_Port, LED_RED1_Pin, 0);
			  HAL_GPIO_WritePin(LED_GREEN1_GPIO_Port, LED_GREEN1_Pin, 1);
			  HAL_GPIO_WritePin(LED_AMBER1_GPIO_Port, LED_AMBER1_Pin, 1);
			  state_trafic_light = 3;
		  	  }
//CONTROL 7 7SEG-LED
		  	if(counter_7LED <= 0){
		  		if(state_trafic_light == 0){
		  			int temp = (TIME_RED_LED - counter_trafic_light)*TRAFIC_SCAN/1000;
		  			led_buffer[2] = temp/10;
		  			led_buffer[3] = temp%10;
		  			temp -= TIME_AMBER_LED*TRAFIC_SCAN/1000;
		  			led_buffer[0] = temp/10;
		  			led_buffer[1] = temp%10;
		  		}
		  		else if(state_trafic_light == 1){
		  			int temp = (TIME_RED_LED - counter_trafic_light)*TRAFIC_SCAN/1000;
		  			led_buffer[2] = temp/10;
		  			led_buffer[3] = temp%10;
		  			led_buffer[0] = temp/10;
		  			led_buffer[1] = temp%10;
		  		}
		  		else if(state_trafic_light == 2){
		  			int temp = (TIME_RED_LED + TIME_GREEN_LED - counter_trafic_light)*TRAFIC_SCAN/1000;
		  			led_buffer[2] = temp/10;
		  			led_buffer[3] = temp%10;
		  			temp += TIME_AMBER_LED*TRAFIC_SCAN/1000;
		  			led_buffer[0] = temp/10;
		  			led_buffer[1] = temp%10;
		  		}
		  		else if(state_trafic_light == 3){
		  			int temp = (TIME_RED_LED + TIME_GREEN_LED + TIME_AMBER_LED - counter_trafic_light)*TRAFIC_SCAN/1000;
		  			led_buffer[2] = temp/10;
		  			led_buffer[3] = temp%10;
		  			led_buffer[0] = temp/10;
		  			led_buffer[1] = temp%10;
		  		}
		  		counter_7LED = 1000/TRAFIC_SCAN;
		  	}
		  	  counter_7LED--;
		  	  counter_trafic_light++;
		  	if(counter_trafic_light >= TIME_RED_LED + TIME_GREEN_LED + TIME_AMBER_LED) counter_trafic_light = 0;
}
