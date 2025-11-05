/*
 * button.h
 *
 *  Created on: Oct 28, 2025
 *      Author: chith
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "main.h"

void button_reading(void);
unsigned char is_button_pressed(int index);
unsigned char is_button_long_pressed(int index);
void fsm_button(void);

#endif /* INC_BUTTON_H_ */
