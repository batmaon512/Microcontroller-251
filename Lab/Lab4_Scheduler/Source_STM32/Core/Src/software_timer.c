/*
 * timer.c
 *
 *  Created on: Oct 13, 2025
 *      Author: chith
 */
#include "software_timer.h"

void setTimer(int index, int duration){
    if(index >= MAX_SOFTWARE_TIMER) return;
    software_timers[index].counter = duration / TIMER_CYCLE;
    software_timers[index].flag = 0;
}

void timer_run(){
    for(int i = 0; i < MAX_SOFTWARE_TIMER; i++){
        if(software_timers[i].counter > 0){
            software_timers[i].counter--;
            if(software_timers[i].counter <= 0){
                software_timers[i].flag = 1;
            }
        }
    }
}

int istimer_flag(int timer_index){
    if(timer_index >= MAX_SOFTWARE_TIMER) return 0;
    if(software_timers[timer_index].flag == 1) {
        software_timers[timer_index].flag = 0;
        return 1;
    }
    return 0;
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim->Instance == TIM2){
		SCH_Update();
	}
}

