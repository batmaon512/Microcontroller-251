/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
#define EXERCISE 8
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
#define USING_FUNCTION_DISLAY7SEG 1
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
#define USING_DATA_STRUCTURE_FOR_SOFTWARE_TIMER 2
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
#elif USING_DATA_STRUCTURE_FOR_SOFTWARE_TIMER == 2 && EXERCISE != 6
#define MAX_SOFTWARE_TIMER 20
#define TIMER_CYCLE 1 // 10ms
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
#elif EXERCISE == 6
int timer0_counter = 0;
int timer0_flag = 0;
int TIMER_CYCLE = 10;

void setTimer0(int duration) {
    timer0_counter = duration / TIMER_CYCLE;
    timer0_flag = 0;
}

void timer_run() {
    if (timer0_counter > 0) {
        timer0_counter--;
    }
    if (timer0_counter == 0) {
        timer0_flag = 1;
    }
}
#endif
//
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
//
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
//
#if EXERCISE == 1

#elif EXERCISE == 2

#elif EXERCISE == 3

#elif EXERCISE == 4

#elif EXERCISE == 5
#define TIME_SWITCH 25
//(x10 ms)
int counter = TIME_SWITCH;
int time_2led = 100;
int hour = 15, minute = 8, second = 50;

void updateClockBuffer(){
if(hour > 99 || hour < 0 || minute > 99 || minute < 0) return;
led_buffer[0] = hour/10;
led_buffer[1] = hour%10;
led_buffer[2] = minute/10;
led_buffer[3] = minute%10;
}
#elif EXERCISE == 6

#elif EXERCISE == 7
int hour = 15, minute = 8, second = 50;

void updateClockBuffer(){
if(hour > 99 || hour < 0 || minute > 99 || minute < 0) return;
led_buffer[0] = hour/10;
led_buffer[1] = hour%10;
led_buffer[2] = minute/10;
led_buffer[3] = minute%10;
}
#elif EXERCISE == 8

#elif EXERCISE == 9

#elif EXERCISE == 10

#endif
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim2);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
#if EXERCISE == 1

#elif EXERCISE == 2

#elif EXERCISE == 3

#elif EXERCISE == 4

#elif EXERCISE == 5

#elif EXERCISE == 6
  setTimer0(1000);
#elif EXERCISE == 7
  setTimer(100, 0); //RED_LED
  setTimer(7, 1); //CLOCK HOUR_MINUTE_SECOND
  setTimer(25, 2); //DISLAY 7 - SEG LED
  setTimer(50, 3);
#elif EXERCISE == 8
  setTimer(25, 0);
#elif EXERCISE == 9

#elif EXERCISE == 10

#endif
  while (1)
  {
#if EXERCISE == 1

#elif EXERCISE == 2

#elif EXERCISE == 3

#elif EXERCISE == 4

#elif EXERCISE == 5
	  second++;
	  if (second >= 60){
		  second = 0;
		  minute++;
	  }
	  if(minute >= 60){
		  minute = 0;
		  hour++;
	  }
	  if(hour >=24){
		  hour = 0;
	  }
	  updateClockBuffer();
	  HAL_Delay(1000);
#elif EXERCISE == 6
	  if(timer0_flag == 1){
	   HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
	   setTimer0(2000);
	   }
#elif EXERCISE == 7
	  if(istimer_flag(0) == 1){
		   HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
		   setTimer(200, 0);
	  }
	  if(istimer_flag(1) == 1){
		  second++;
		  if (second >= 60){
			  second = 0;
			  minute++;
		  }
		  if(minute >= 60){
			  minute = 0;
			  hour++;
		  }
		  if(hour >=24){
			  hour = 0;
		  }
		  updateClockBuffer();
		  setTimer(100, 1);
	  }
	  if(istimer_flag(2) == 1){
		  update7SEG(index_led++);
		  if(index_led > 3) index_led = 0;
		  setTimer(25, 2);
	  }
	  if(istimer_flag(3) == 1){
		  HAL_GPIO_TogglePin(DOT_GPIO_Port, DOT_Pin);
		  setTimer(100, 3);
	  }
#elif EXERCISE == 8
	  if(istimer_flag(0) == 1){
		  updateLEDMatrix(index_led_matrix++);
		  if(index_led_matrix > 7) index_led_matrix = 0;
		  setTimer(1, 0);
	  }
#elif EXERCISE == 9

#elif EXERCISE == 10

#endif
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 7999;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 9;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, ENM0_Pin|ENM1_Pin|DOT_Pin|LED_RED_Pin
                          |EN0_Pin|EN1_Pin|EN2_Pin|EN3_Pin
                          |ENM2_Pin|ENM3_Pin|ENM4_Pin|ENM5_Pin
                          |ENM6_Pin|ENM7_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, SEG0_Pin|SEG1_Pin|SEG2_Pin|ROW2_Pin
                          |ROW3_Pin|ROW4_Pin|ROW5_Pin|ROW6_Pin
                          |ROW7_Pin|SEG3_Pin|SEG4_Pin|SEG5_Pin
                          |SEG6_Pin|ROW0_Pin|ROW1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : ENM0_Pin ENM1_Pin DOT_Pin LED_RED_Pin
                           EN0_Pin EN1_Pin EN2_Pin EN3_Pin
                           ENM2_Pin ENM3_Pin ENM4_Pin ENM5_Pin
                           ENM6_Pin ENM7_Pin */
  GPIO_InitStruct.Pin = ENM0_Pin|ENM1_Pin|DOT_Pin|LED_RED_Pin
                          |EN0_Pin|EN1_Pin|EN2_Pin|EN3_Pin
                          |ENM2_Pin|ENM3_Pin|ENM4_Pin|ENM5_Pin
                          |ENM6_Pin|ENM7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : SEG0_Pin SEG1_Pin SEG2_Pin ROW2_Pin
                           ROW3_Pin ROW4_Pin ROW5_Pin ROW6_Pin
                           ROW7_Pin SEG3_Pin SEG4_Pin SEG5_Pin
                           SEG6_Pin ROW0_Pin ROW1_Pin */
  GPIO_InitStruct.Pin = SEG0_Pin|SEG1_Pin|SEG2_Pin|ROW2_Pin
                          |ROW3_Pin|ROW4_Pin|ROW5_Pin|ROW6_Pin
                          |ROW7_Pin|SEG3_Pin|SEG4_Pin|SEG5_Pin
                          |SEG6_Pin|ROW0_Pin|ROW1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
#if EXERCISE == 1
#define TIME_SWITCH 50
//(x10 ms)
int LED_PA5 = 100;
int counter = TIME_SWITCH;
int state = 0;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(counter <= 0){
		if(state == 0){
			HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 1);
			HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 0);
			display7SEG(1);
			state = 1;
		}
		else if(state == 1){
			HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 0);
			HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 1);
			display7SEG(2);
			state = 0;
		}
		counter = TIME_SWITCH;
	}
	if(LED_PA5 <= 0){
		 LED_PA5 = 100;
		 HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
	 }
	LED_PA5--;
	counter--;
}
#elif EXERCISE == 2
#define TIME_SWITCH 50
//(x10 ms)
int counter = TIME_SWITCH;
int LED_PA5 = 100;
int state = 0;
int time_2led = 100;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(time_2led <= 0){
		HAL_GPIO_TogglePin(DOT_GPIO_Port, DOT_Pin);
		time_2led = 100;
	}
	if(counter <= 0){
		if(state == 0){
			HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, 1);
			HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, 1);
			HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 1);
			HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 0);
			display7SEG(1);
			state = 1;
		}
		else if(state == 1){
			HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, 1);
			HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, 1);
			HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 0);
			HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 1);
			display7SEG(2);
			state = 2;
		}
		else if(state == 2){
			HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, 1);
			HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, 0);
			HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 1);
			HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 1);
			display7SEG(3);
			state = 3;
		}
		else if(state == 3){
			HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, 0);
			HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, 1);
			HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 1);
			HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 1);
			display7SEG(0);
			state = 0;
		}
		counter = TIME_SWITCH;
	}
	if(LED_PA5 <= 0){
		 LED_PA5 = 100;
		 HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
	 }
	counter--;
	time_2led--;
	LED_PA5--;
}
#elif EXERCISE == 3
#define TIME_SWITCH 50
//(x10 ms)
int counter = TIME_SWITCH;
int LED_PA5 = 100;
int time_2led = 100;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(time_2led <= 0){
		HAL_GPIO_TogglePin(DOT_GPIO_Port, DOT_Pin);
		time_2led = 100;
	}
	if(counter <= 0){
		update7SEG(index_led++);
		if(index_led > 3) index_led = 0;
		counter = TIME_SWITCH;
	}
	if(LED_PA5 <= 0){
		 LED_PA5 = 100;
		 HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
	 }
	LED_PA5--;
	counter--;
	time_2led--;
}
#elif EXERCISE == 4
#define TIME_SWITCH 25
//(x10 ms)
int counter = TIME_SWITCH;
int LED_PA5 = 100;
int time_2led = 100;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(time_2led <= 0){
		HAL_GPIO_TogglePin(DOT_GPIO_Port, DOT_Pin);
		time_2led = 100;
	}
	if(counter <= 0){
		update7SEG(index_led++);
		if(index_led > 3) index_led = 0;
		counter = TIME_SWITCH;
	}
	if(LED_PA5 <= 0){
		 LED_PA5 = 100;
		 HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
	 }
	LED_PA5--;
	counter--;
	time_2led--;
}
#elif EXERCISE == 5
int LED_PA5 = 100;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(time_2led <= 0){
		HAL_GPIO_TogglePin(DOT_GPIO_Port, DOT_Pin);
		time_2led = 100;
	}
	if(counter <= 0){
		update7SEG(index_led++);
		if(index_led > 3) index_led = 0;
		counter = TIME_SWITCH;
	}
	if(LED_PA5 <= 0){
		 LED_PA5 = 100;
		 HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
	 }
	LED_PA5--;
	counter--;
	time_2led--;
}
#elif EXERCISE == 6
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    timer_run();
}
#elif EXERCISE == 7
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
timer_run();
}
#elif EXERCISE == 8
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
timer_run();
}
#elif EXERCISE == 9
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{

}
#elif EXERCISE == 10
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{

}
#endif
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
