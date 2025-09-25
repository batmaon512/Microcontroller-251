#ifndef INC_EXERCISES_TIMER_DRIVER_H_
#define INC_EXERCISES_TIMER_DRIVER_H_

#include "main.h"

//==============================================================================
// Software Timer Driver
//==============================================================================
#define MAX_SOFTWARE_TIMER 10
#define TIMER_CYCLE 1 // Timer interrupt period is 10ms
#define USING_DATA_STRUCTURE_FOR_SOFTWARE_TIMER 3
#define USING_FUNCTION_DISLAY7SEG 1
void setTimer(int duration, int index);
int istimer_flag(int index);
void timer_run();


//==============================================================================
// 7-Segment LED Driver
//==============================================================================
extern int led_buffer[4];
extern int index_led;
void display7SEG(int num);
void update7SEG(int index);


//==============================================================================
// 8x8 LED Matrix Driver
//==============================================================================
extern uint8_t matrix_buffer[8];
extern int index_led_matrix;
void updateLEDMatrix(int index);


#endif /* INC_EXERCISES_DRIVERS_H_ */
