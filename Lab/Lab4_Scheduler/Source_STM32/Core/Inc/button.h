/*
 * button.h
 *
 *  Created on: Oct 28, 2025
 *      Author: chith
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "main.h"

#define BUTTON_IS_PRESSED GPIO_PIN_RESET
#define BUTTON_IS_RELEASED GPIO_PIN_SET
void init_button();
void button_reading(void);
unsigned char is_button_pressed(int index);
unsigned char is_button_long_pressed(int index);
unsigned char event_button(int index);
unsigned char event_button_long(int index);
void clear_event_button(int index);
void clear_event_button_long(int index);
#endif /* INC_BUTTON_H_ */
