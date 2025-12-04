/*
 * timer.h
 *
 *  Created on: Dec 3, 2025
 *      Author: chith
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

#include "main.h"
#define MAX_SOFTWARE_TIMER 10
#define TIMER_CYCLE 10 // Timer interrupt period is 10ms

typedef struct SoftwareTimer{
    int counter;
    int flag;
} SoftwareTimer;

extern SoftwareTimer software_timers[MAX_SOFTWARE_TIMER];

void setTimer(int duration, int index);
int istimer_flag(int index);
void timer_run();

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

#endif /* INC_SOFTWARE_TIMER_H_ */
