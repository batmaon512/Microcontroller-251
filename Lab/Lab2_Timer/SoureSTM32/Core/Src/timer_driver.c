#include "timer_driver.h"
//==============================================================================
// Software Timer Implementation
//==============================================================================
#if USING_DATA_STRUCTURE_FOR_SOFTWARE_TIMER == 1
//IMPLEMENT DATA STRUCTURE FOR SOFTWARE TIMER
#define MAX_SOFTWARE_TIMER 20
typedef struct Node {
    int counter;
	int timer_idex;
    struct Node* next;
} Node;

Node* createNode(int counter, int timer_index) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if(newNode == NULL) return NULL;
    newNode->counter = counter;
	newNode->timer_idex = timer_index;
    newNode->next = NULL;
    return newNode;
}
int timer_flag[MAX_SOFTWARE_TIMER] = {0};
Node* timer_active_head;
void setTimer(int duration, int timer_index){
	timer_flag[timer_index] = 0;
	if(timer_active_head == NULL){
		timer_active_head = createNode(duration, timer_index);
		return;
	}
	if(timer_active_head->counter >= duration){
		timer_active_head->counter = timer_active_head->counter - duration;
		Node* newNode = createNode(duration, timer_index);
		newNode->next = timer_active_head;
		timer_active_head = newNode;
		return;
	}
	int temp_duration = duration - timer_active_head->counter ;
	Node* temp = timer_active_head->next;
	Node* pre = timer_active_head;
	while(temp != NULL){
		if(temp->counter >= temp_duration){
			temp->counter = temp->counter - temp_duration;
			Node* newNode = createNode(temp_duration, timer_index);
			newNode->next = temp;
			pre->next = newNode;
			return;
		}
		temp_duration = temp_duration - temp->counter;
		pre = temp;
		temp = temp->next;
	}
		pre->next = createNode(temp_duration, timer_index);
	return;
}
void timer_run(){
	if(timer_active_head == NULL) return;
	if(timer_active_head->counter > 0) timer_active_head->counter--;
	else{
		while (timer_active_head != NULL && timer_active_head->counter <= 0)
		{
			timer_flag[timer_active_head->timer_idex] = 1;
			Node* temp = timer_active_head;
			timer_active_head = timer_active_head->next;
			free(temp);
			temp = NULL;
		}
	}
}
int istimer_flag(int timer_index){
	if(timer_flag[timer_index] == 1) return 1;
	else return 0;
}
#elif USING_DATA_STRUCTURE_FOR_SOFTWARE_TIMER == 2
typedef struct {
    int counter;
    int flag;
} SoftwareTimer;

SoftwareTimer software_timers[MAX_SOFTWARE_TIMER];

void setTimer(int duration, int index){
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
        software_timers[timer_index].flag = 0; // Tự động xóa cờ sau khi đọc
        return 1;
    }
    return 0;
}
#endif
//==============================================================================
// 7-Segment LED Driver
//==============================================================================
#if USING_FUNCTION_DISLAY7SEG == 1
//USING ONLY FOR LAB 2 BECAUSE PIN SEG CONTROL SAME GPIO_PORT
const uint8_t seg_code[10] = {
    0b1000000, // 0
    0b1111001, // 1
    0b0100100, // 2
    0b0110000, // 3
    0b0011001, // 4
    0b0010010, // 5
    0b0000010, // 6
    0b1111000, // 7
    0b0000000, // 8
    0b0010000  // 9
};
void display7SEG(int num){
	 if(num > 9 || num < 0) return;
	 HAL_GPIO_WritePin(SEG0_GPIO_Port, 0b11111111, 0);
	 HAL_GPIO_WritePin(SEG0_GPIO_Port, seg_code[num], 1);

}
#elif  USING_FUNCTION_DISLAY7SEG == 2
void display7SEG(int num){
	 if(num > 9 || num < 0) return;
	 HAL_GPIO_WritePin(SEG0_GPIO_Port, SEG0_Pin, num==1 || num==4);
	 HAL_GPIO_WritePin(SEG1_GPIO_Port, SEG1_Pin, num==5 || num==6);
	 HAL_GPIO_WritePin(SEG2_GPIO_Port, SEG2_Pin, num==2);
	 HAL_GPIO_WritePin(SEG3_GPIO_Port, SEG3_Pin, num==1 || num==4 || num==7);
	 HAL_GPIO_WritePin(SEG4_GPIO_Port, SEG4_Pin, !(num == 0 || num == 2 || num == 6 || num == 8));
	 HAL_GPIO_WritePin(SEG5_GPIO_Port, SEG5_Pin, num==1 || num==2 || num==3 || num==7);
	 HAL_GPIO_WritePin(SEG6_GPIO_Port, SEG6_Pin, num== 0 || num==1 || num==7);

}
#endif

const int MAX_LED = 4;
int index_led = 0;
int led_buffer[4] = {1, 2, 3, 4};
void update7SEG(int index){
	 switch (index){
		 case 0:
		 //Display the first 7SEG with led_buffer[0]
				HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, 1);
				HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, 1);
				HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 1);
				HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 0);
				display7SEG(led_buffer[0]);
		 break;
		 case 1:
		 //Display the second 7SEG with led_buffer[1]
				HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, 1);
				HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, 1);
				HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 0);
				HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 1);
				display7SEG(led_buffer[1]);
		 break;
		 case 2:
		 //Display the third 7SEG with led_buffer[2]
				HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, 1);
				HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, 0);
				HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 1);
				HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 1);
				display7SEG(led_buffer[2]);
		 break;
		 case 3:
		 //Display the forth 7SEG with led_buffer[3]
				HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, 0);
				HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, 1);
				HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 1);
				HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 1);
				display7SEG(led_buffer[3]);
		 break;
		 default:
		 break;
	 }
 }
//==============================================================================
// 8x8 LED Matrix Driver
//==============================================================================
 const int MAX_LED_MATRIX = 8;
 int index_led_matrix = 0;
 uint8_t matrix_buffer[8] = { 0x00, 0x7E, 0x09, 0x09, 0x09, 0x7E, 0x00, 0x00};
//USING THIS CODE IF ONLY THIS LAB BECAUSE THEIR ARE SAME PORT
 void updateLEDMatrix(int index){
	 uint16_t matrix_pin_for_buffer0 = matrix_buffer[index];
	 uint16_t matrix_pin_for_buffer1 = ~matrix_buffer[index];
		matrix_pin_for_buffer0 = matrix_pin_for_buffer0<<8;
		matrix_pin_for_buffer1 = matrix_pin_for_buffer1<<8;
		HAL_GPIO_WritePin(ROW0_GPIO_Port, matrix_pin_for_buffer0, 0);
		HAL_GPIO_WritePin(ROW0_GPIO_Port, matrix_pin_for_buffer1, 1);
	 switch (index){
		 case 0:
			HAL_GPIO_WritePin(ENM0_GPIO_Port, ENM0_Pin, 0);
			HAL_GPIO_WritePin(ENM1_GPIO_Port, ENM1_Pin, 1);
			HAL_GPIO_WritePin(ENM2_GPIO_Port, ENM2_Pin, 1);
			HAL_GPIO_WritePin(ENM3_GPIO_Port, ENM3_Pin, 1);
			HAL_GPIO_WritePin(ENM4_GPIO_Port, ENM4_Pin, 1);
			HAL_GPIO_WritePin(ENM5_GPIO_Port, ENM5_Pin, 1);
			HAL_GPIO_WritePin(ENM6_GPIO_Port, ENM6_Pin, 1);
			HAL_GPIO_WritePin(ENM7_GPIO_Port, ENM7_Pin, 1);
		 break;
		 case 1:
			 HAL_GPIO_WritePin(ENM0_GPIO_Port, ENM0_Pin, 1);
			 HAL_GPIO_WritePin(ENM1_GPIO_Port, ENM1_Pin, 0);
			 HAL_GPIO_WritePin(ENM2_GPIO_Port, ENM2_Pin, 1);
			 HAL_GPIO_WritePin(ENM3_GPIO_Port, ENM3_Pin, 1);
			 HAL_GPIO_WritePin(ENM4_GPIO_Port, ENM4_Pin, 1);
			 HAL_GPIO_WritePin(ENM5_GPIO_Port, ENM5_Pin, 1);
			 HAL_GPIO_WritePin(ENM6_GPIO_Port, ENM6_Pin, 1);
			 HAL_GPIO_WritePin(ENM7_GPIO_Port, ENM7_Pin, 1);
		 break;
		 case 2:
			 HAL_GPIO_WritePin(ENM0_GPIO_Port, ENM0_Pin, 1);
			 HAL_GPIO_WritePin(ENM1_GPIO_Port, ENM1_Pin, 1);
			 HAL_GPIO_WritePin(ENM2_GPIO_Port, ENM2_Pin, 0);
			 HAL_GPIO_WritePin(ENM3_GPIO_Port, ENM3_Pin, 1);
			 HAL_GPIO_WritePin(ENM4_GPIO_Port, ENM4_Pin, 1);
			 HAL_GPIO_WritePin(ENM5_GPIO_Port, ENM5_Pin, 1);
			 HAL_GPIO_WritePin(ENM6_GPIO_Port, ENM6_Pin, 1);
			 HAL_GPIO_WritePin(ENM7_GPIO_Port, ENM7_Pin, 1);
		 break;
		 case 3:
			 HAL_GPIO_WritePin(ENM0_GPIO_Port, ENM0_Pin, 1);
			 HAL_GPIO_WritePin(ENM1_GPIO_Port, ENM1_Pin, 1);
			 HAL_GPIO_WritePin(ENM2_GPIO_Port, ENM2_Pin, 1);
			 HAL_GPIO_WritePin(ENM3_GPIO_Port, ENM3_Pin, 0);
			 HAL_GPIO_WritePin(ENM4_GPIO_Port, ENM4_Pin, 1);
			 HAL_GPIO_WritePin(ENM5_GPIO_Port, ENM5_Pin, 1);
			 HAL_GPIO_WritePin(ENM6_GPIO_Port, ENM6_Pin, 1);
			 HAL_GPIO_WritePin(ENM7_GPIO_Port, ENM7_Pin, 1);
		 break;
		 case 4:
			 HAL_GPIO_WritePin(ENM0_GPIO_Port, ENM0_Pin, 1);
			 HAL_GPIO_WritePin(ENM1_GPIO_Port, ENM1_Pin, 1);
			 HAL_GPIO_WritePin(ENM2_GPIO_Port, ENM2_Pin, 1);
			 HAL_GPIO_WritePin(ENM3_GPIO_Port, ENM3_Pin, 1);
			 HAL_GPIO_WritePin(ENM4_GPIO_Port, ENM4_Pin, 0);
			 HAL_GPIO_WritePin(ENM5_GPIO_Port, ENM5_Pin, 1);
			 HAL_GPIO_WritePin(ENM6_GPIO_Port, ENM6_Pin, 1);
			 HAL_GPIO_WritePin(ENM7_GPIO_Port, ENM7_Pin, 1);
		 break;
		 case 5:
			 HAL_GPIO_WritePin(ENM0_GPIO_Port, ENM0_Pin, 1);
			 HAL_GPIO_WritePin(ENM1_GPIO_Port, ENM1_Pin, 1);
			 HAL_GPIO_WritePin(ENM2_GPIO_Port, ENM2_Pin, 1);
			 HAL_GPIO_WritePin(ENM3_GPIO_Port, ENM3_Pin, 1);
			 HAL_GPIO_WritePin(ENM4_GPIO_Port, ENM4_Pin, 1);
			 HAL_GPIO_WritePin(ENM5_GPIO_Port, ENM5_Pin, 0);
			 HAL_GPIO_WritePin(ENM6_GPIO_Port, ENM6_Pin, 1);
			 HAL_GPIO_WritePin(ENM7_GPIO_Port, ENM7_Pin, 1);
		 break;
		 case 6:
			 HAL_GPIO_WritePin(ENM0_GPIO_Port, ENM0_Pin, 1);
			 HAL_GPIO_WritePin(ENM1_GPIO_Port, ENM1_Pin, 1);
			 HAL_GPIO_WritePin(ENM2_GPIO_Port, ENM2_Pin, 1);
			 HAL_GPIO_WritePin(ENM3_GPIO_Port, ENM3_Pin, 1);
			 HAL_GPIO_WritePin(ENM4_GPIO_Port, ENM4_Pin, 1);
			 HAL_GPIO_WritePin(ENM5_GPIO_Port, ENM5_Pin, 1);
			 HAL_GPIO_WritePin(ENM6_GPIO_Port, ENM6_Pin, 0);
			 HAL_GPIO_WritePin(ENM7_GPIO_Port, ENM7_Pin, 1);
		 break;
		 case 7:
			 HAL_GPIO_WritePin(ENM0_GPIO_Port, ENM0_Pin, 1);
			 HAL_GPIO_WritePin(ENM1_GPIO_Port, ENM1_Pin, 1);
			 HAL_GPIO_WritePin(ENM2_GPIO_Port, ENM2_Pin, 1);
			 HAL_GPIO_WritePin(ENM3_GPIO_Port, ENM3_Pin, 1);
			 HAL_GPIO_WritePin(ENM4_GPIO_Port, ENM4_Pin, 1);
			 HAL_GPIO_WritePin(ENM5_GPIO_Port, ENM5_Pin, 1);
			 HAL_GPIO_WritePin(ENM6_GPIO_Port, ENM6_Pin, 1);
			 HAL_GPIO_WritePin(ENM7_GPIO_Port, ENM7_Pin, 0);
		 break;
		  default:
		  break;
	  }
  }
