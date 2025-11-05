/*
 * timer.h
 *
 *  Created on: Oct 13, 2025
 *      Author: chith
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

#include "main.h"
#include "button.h"

void setTimer(int duration, int index);
int istimer_flag(int index);
void timer_run();

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

#endif /* INC_SOFTWARE_TIMER_H_ */
