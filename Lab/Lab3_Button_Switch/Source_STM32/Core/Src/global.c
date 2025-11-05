/*
 * global.c
 *
 *  Created on: Nov 3, 2025
 *      Author: chith
 */
#include "global.h"
//==============================================================================
// Software Timer
//==============================================================================
SoftwareTimer software_timers[MAX_SOFTWARE_TIMER] = {0};

//==============================================================================
// Button
//==============================================================================
uint16_t BUTTON_MAP[MAX_BUTTONS] = {BUTTON0_Pin, BUTTON1_Pin, BUTTON2_Pin};
GPIO_TypeDef* BUTTON_PORT_MAP[MAX_BUTTONS] = {BUTTON0_GPIO_Port, BUTTON1_GPIO_Port, BUTTON2_GPIO_Port};
GPIO_PinState buttonBuffer[MAX_BUTTONS];
GPIO_PinState debounceButtonBuffer[MAX_BUTTONS];
uint16_t counterButtonBuffer[MAX_BUTTONS] = {0};
uint8_t flagButtonLongPress[MAX_BUTTONS] = {0};
uint16_t counterButtonLongPress[MAX_BUTTONS] = {0};
uint8_t flagPress[MAX_BUTTONS] = {0};
uint8_t flagLongPress[MAX_BUTTONS] = {0};
enum ButtonState buttonState[MAX_BUTTONS];
//==============================================================================
// Display
//==============================================================================
int index_led = 0;
int led_buffer[MAX_LED] = {0};
//==============================================================================
// Trafic Light
//==============================================================================
int TempConfigure;

int32_t TIME_RED_LED = 5000/TRAFIC_SCAN;
int32_t TIME_AMBER_LED = 2000/TRAFIC_SCAN;
int32_t TIME_GREEN_LED = 3000/TRAFIC_SCAN;

int32_t counter_trafic_light = 0;
int8_t state_trafic_light = -1;
int32_t counter_7LED = 0;
//==============================================================================
// Configure Mode
//==============================================================================
int32_t counter_configure_mode = 0;
//==============================================================================
// Initial
//==============================================================================
void init_running(){
	for(int i = 0; i < MAX_BUTTONS; i++){
		buttonBuffer[i] = GPIO_PIN_SET;
		debounceButtonBuffer[i] = GPIO_PIN_SET;
		buttonState[i] = BUTTON_RELEASED;
	}
}
//==============================================================================
// GLOBAL VAR
//==============================================================================
uint8_t mode = 0;
