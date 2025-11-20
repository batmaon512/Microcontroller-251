/*
 * global.h
 *
 *  Created on: Nov 3, 2025
 *      Author: chith
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "main.h"

//==============================================================================
// Software Timer
//==============================================================================
#define MAX_SOFTWARE_TIMER 10
#define TIMER_CYCLE 10 // Timer interrupt period is 10ms

typedef struct SoftwareTimer{
    int counter;
    int flag;
} SoftwareTimer;

extern SoftwareTimer software_timers[MAX_SOFTWARE_TIMER];

//==============================================================================
// Button
//==============================================================================
#define MAX_BUTTONS 3
#define TIME_BOUNCING 10 //ms
#define TIME_BUTTON_SCAN 10 //ms
#define TIME_LONG_PRESS 500 //ms
//==============================================================================
// Display
//==============================================================================
#define MAX_LED 4
extern int led_buffer[MAX_LED];
extern int index_led;
//==============================================================================
// Trafic Light
//==============================================================================
#define TRAFIC_SCAN 50 //ms

extern int TempConfigure;
extern int32_t TIME_RED_LED;
extern int32_t TIME_AMBER_LED;
extern int32_t TIME_GREEN_LED;

extern int32_t counter_trafic_light;
extern int8_t state_trafic_light;
extern int32_t counter_7LED;
//==============================================================================
// Configure Mode
//==============================================================================
extern int32_t counter_configure_mode;
//==============================================================================
// Initial
//==============================================================================
void init_running(void);
//==============================================================================
// GLOBAL VAR
//==============================================================================
#define TIME_SCAN 50 //ms
extern uint8_t mode;


#endif /* INC_GLOBAL_H_ */
