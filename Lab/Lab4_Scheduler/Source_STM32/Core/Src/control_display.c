/*
 * control_display.c
 *
 *  Created on: Oct 28, 2025
 *      Author: chith
 */

#include "control_display.h"

void display7SEG(int num){
	 if(num > 9 || num < 0) return;
	 HAL_GPIO_WritePin(SEG0_GPIO_Port, SEG0_Pin, num==1 || num==4);
	 HAL_GPIO_WritePin(SEG1_GPIO_Port, SEG1_Pin, num==5 || num==6);
	 HAL_GPIO_WritePin(SEG2_GPIO_Port, SEG2_Pin, num==2);
	 HAL_GPIO_WritePin(SEG3_GPIO_Port, SEG3_Pin, num==1 || num==4 || num==7);
	 HAL_GPIO_WritePin(SEG4_GPIO_Port, SEG4_Pin, !(num == 0 || num == 2 || num == 6 || num == 8));
	 HAL_GPIO_WritePin(SEG5_GPIO_Port, SEG5_Pin, num==1 || num==2 || num==3 || num==7);
	 HAL_GPIO_WritePin(SEG6_GPIO_Port, SEG6_Pin, num== 0 || num==1 || num==7);

}

uint16_t ENMAP[MAX_LED] = {EN0_Pin, EN1_Pin, EN2_Pin, EN3_Pin};

void update7SEG(int index){
			if(index >= MAX_LED || index < 0) return;
			HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin | EN1_Pin |  EN2_Pin | EN3_Pin, SET);
			display7SEG(led_buffer[index]);
			HAL_GPIO_WritePin(EN0_GPIO_Port, ENMAP[index], RESET);
}

