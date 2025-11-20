#ifndef __SCHEDULER_H
#define __SCHEDULER_H
#include "main.h"
#include <stdlib.h>

typedef struct sTask{
	void (*pTask)(void);
	uint32_t Delay;
	uint32_t Period;
	uint8_t RunMe;
} sTask;

typedef struct Node{
    uint16_t data;
    struct Node *next;
} Node;

Node* create_node(uint16_t value);

#define MAX_TASK 30

void insert(Node* i);

void SCH_Intit(void);
void SCH_Update(void);
void SCH_Dispatch_Tasks(void);
uint16_t SCH_Add_Task(void(*pFunction)(), uint32_t DELAY, uint32_t PERIOD);
uint8_t SCH_Delete_Task(uint16_t taskID);
void SCH_Go_To_Sleep();
void SCH_Report_Status(void);

//IWDG_HandleTypeDef hiwdg;
//static uint32_t counter_for_watchdog = 0;
//
//void MX_IWDG_Init(void){
//    hiwdg.Instance = IWDG;
//    hiwdg.Init.Prescaler = IWDG_PRESCALER_32;
//    hiwdg.Init.Reload = 4095;
//    if (HAL_IWDG_Init(&hiwdg) != HAL_OK) {
//        Error_Handler();
//    }
//}
//
//void Watchdog_Refresh(void){
//    HAL_IWDG_Refresh(&hiwdg);
//}
//
//unsigned char Is_Watchdog_Reset(void){
//    if(counter_for_watchdog > 3){
//        return 1;
//    }
//    return 0;
//}
//
//void Watchdog_Counting(void){
//    counter_for_watchdog++;
//}
//
//void Reset_Watchdog_Counting(void){
//    counter_for_watchdog = 0;
//}

#endif
