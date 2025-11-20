/*
 * scheduler.c
 *
 *  Created on: Nov 18, 2025
 *      Author: chith
 */

#include "scheduler.h"

sTask TaskList[MAX_TASK];
Node* WaitingList;
Node* ActiveList;
uint16_t numTask;
unsigned char Error_code_G = 0;
Node* create_node(uint16_t value) {
    Node *n = (Node*)malloc(sizeof(Node));
    if(!n) return NULL;
    n->data = value;
    n->next = NULL;
    return n;
}
void insert(Node* i){
	if(WaitingList == NULL){
		WaitingList = i;
		WaitingList->next = NULL;
		return;
	}
	Node* prev = NULL;
	Node* temp = WaitingList;
	while(temp != NULL && TaskList[i->data].Delay > TaskList[temp->data].Delay){
		TaskList[i->data].Delay -= TaskList[temp->data].Delay;
		prev = temp;
		temp = temp->next;
	}
	if(temp != NULL) TaskList[temp->data].Delay -= TaskList[i->data].Delay;
	if(prev == NULL){
		i->next = WaitingList;
		WaitingList = i;
		return;
	}
	i->next = prev->next;
	prev->next = i;
	return;
}
void SCH_Intit(void){
	WaitingList = NULL;
	ActiveList = NULL;
	numTask = 0;
	for(int i = 0; i < MAX_TASK; i++){
		TaskList[i].Delay = 0;
		TaskList[i].Period = 0;
		TaskList[i].RunMe = 0;
		TaskList[i].pTask = 0x0000;
	}
//	MX_IWDG_Init();
}
void SCH_Update(void){
//	Watchdog_Refresh();
	if(numTask <= 0) return;
	while(WaitingList != NULL && TaskList[WaitingList->data].Delay <= 0){
		uint16_t temp = WaitingList->data;
		TaskList[temp].RunMe++;
		Node* add = create_node(temp);
		add->next = ActiveList;
		ActiveList = add;
		Node* remove = WaitingList;
		WaitingList = WaitingList->next;
		if(TaskList[temp].Period > 0){
			TaskList[temp].Delay = TaskList[temp].Period;
			insert(remove);
		}
		else {
			free(remove);
			numTask--;
		}
	}
	if(WaitingList == NULL) return;
	TaskList[WaitingList->data].Delay--;
}
void SCH_Dispatch_Tasks(void){
	Node* temp = ActiveList;
	while(temp != NULL){
		while(TaskList[temp->data].RunMe > 0){
			(*TaskList[temp->data].pTask)();
			TaskList[temp->data].RunMe--;
		}
		Node* A = ActiveList;
			Node* prevA = ActiveList;
			while(A != NULL && A->data != temp->data){
				prevA = A;
				A = A->next;
			}
			if(A != NULL){
				if(A == ActiveList){
					ActiveList = ActiveList->next;
				}
				else{
					prevA->next = A->next;
				}
				free(A);
			}
		temp = temp->next;
	}

//	Watchdog_Counting();
//
//	if(Is_Watchdog_Reset()){
//
//	}

	SCH_Go_To_Sleep();
}
uint16_t SCH_Add_Task(void(*pFunction)(), uint32_t DELAY, uint32_t PERIOD){
	if(numTask >= MAX_TASK) return MAX_TASK;
	int ID;
	for(int i = 0; i < MAX_TASK; i++){
		if(TaskList[i].pTask == 0) {ID = i; break;}
	}
	TaskList[ID].Delay = DELAY/TIMER_CYCLE;
	TaskList[ID].Period = PERIOD/TIMER_CYCLE;
	TaskList[ID].pTask = pFunction;
	TaskList[ID].RunMe = 0;
	Node* temp = create_node(ID);
	insert(temp);

	numTask++;
	return ID;
}
uint8_t SCH_Delete_Task(uint16_t taskID){
	if(WaitingList == NULL) return 0;
	Node* pre = WaitingList;
	Node* temp = WaitingList;
	while(temp != NULL && temp->data != taskID){
		pre = temp;
		temp = temp->next;
	}
	if(temp == NULL) return 0;
	numTask--;
	if(temp->next != NULL){
		TaskList[temp->next->data].Delay += TaskList[temp->data].Delay;
	}
	if(temp == WaitingList){
		WaitingList = WaitingList->next;
		free(temp);
		return 1;
	}
	pre->next = temp->next;



	TaskList[temp->data].Delay = 0;
	TaskList[temp->data].Period = 0;
	TaskList[temp->data].RunMe = 0;
	TaskList[temp->data].pTask = 0x0000;
	free(temp);
	return 1;
}
void SCH_Go_To_Sleep(){
	HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);
}

void SCH_Report_Status(void) {
#ifdef SCH_REPORT_ERRORS

    // ONLY APPLIES IF WE ARE REPORTING ERRORS
    // Check for a new error code
    if (Error_code_G != Last_error_code_G) {

        // Negative logic on LEDs assumed
        Error_port = 255 - Error_code_G;
        Last_error_code_G = Error_code_G;

        if (Error_code_G != 0){
            Error_tick_count_G = 60000;
        }
        else {
            Error_tick_count_G = 0;
        }
    }
    else {
        if (Error_tick_count_G != 0){
            if (--Error_tick_count_G == 0) {
                Error_code_G = 0; // Reset error code
            }
        }
    }
#endif
}
