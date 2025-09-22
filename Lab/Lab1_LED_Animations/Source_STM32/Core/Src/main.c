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
#define EXERCISE 5
#if EXERCISE == 1
	#define LED_RED_Pin GPIO_PIN_5
	#define LED_RED_GPIO_Port GPIOA
	#define LED_YELLOW_Pin GPIO_PIN_6
	#define LED_YELLOW_GPIO_Port GPIOA
#elif EXERCISE == 2
	#define LED_RED_Pin GPIO_PIN_5
	#define LED_RED_GPIO_Port GPIOA
	#define LED_GREEN_Pin GPIO_PIN_7
	#define LED_GREEN_GPIO_Port GPIOA
	#define LED_YELLOW_Pin GPIO_PIN_6
	#define LED_YELLOW_GPIO_Port GPIOA
#elif EXERCISE == 3
//CONFIGE TIMER FOR TRAFFIC LIGHT
//NOTE: SUM OF TIME 3 LED OF TRAFFIC LIGHT MUST BE EQUAL SUM_TIME_LED
//Real Time = Time x 10 ms
//YELLOW_TIME + GREEN_TIME == RED_TIME_LED OTHER
	#define SUM_TIME_LED 1000

	#define TIME_LED_RED_1 500
	#define TIME_LED_GREEN_1 300
	#define TIME_LED_YELLOW_1 200

	#define TIME_LED_RED_2 500
	#define TIME_LED_GREEN_2 300
	#define TIME_LED_YELLOW_2 200
//
	#define LED_RED_1_Pin GPIO_PIN_5
	#define LED_RED_1_GPIO_Port GPIOA
	#define LED_GREEN_1_Pin GPIO_PIN_7
	#define LED_GREEN_1_GPIO_Port GPIOA
	#define LED_YELLOW_1_Pin GPIO_PIN_6
	#define LED_YELLOW_1_GPIO_Port GPIOA
	#define LED_RED_2_Pin GPIO_PIN_0
	#define LED_RED_2_GPIO_Port GPIOB
	#define LED_GREEN_2_Pin GPIO_PIN_2
	#define LED_GREEN_2_GPIO_Port GPIOB
	#define LED_YELLOW_2_Pin GPIO_PIN_1
	#define LED_YELLOW_2_GPIO_Port GPIOB
#elif EXERCISE == 4
#define PIN_A_Pin GPIO_PIN_0
#define PIN_A_GPIO_Port GPIOB
#define PIN_B_Pin GPIO_PIN_1
#define PIN_B_GPIO_Port GPIOB
#define PIN_C_Pin GPIO_PIN_2
#define PIN_C_GPIO_Port GPIOB
#define PIN_D_Pin GPIO_PIN_3
#define PIN_D_GPIO_Port GPIOB
#define PIN_E_Pin GPIO_PIN_4
#define PIN_E_GPIO_Port GPIOB
#define PIN_F_Pin GPIO_PIN_5
#define PIN_F_GPIO_Port GPIOB
#define PIN_G_Pin GPIO_PIN_6
#define PIN_G_GPIO_Port GPIOB

//DEFINE FUNCTION
 void display7SEG(int counter){
	 if(counter >= 10 || counter < 0) return;
	 HAL_GPIO_WritePin(PIN_A_GPIO_Port, PIN_A_Pin, counter==1 || counter==4);
	 HAL_GPIO_WritePin(PIN_B_GPIO_Port, PIN_B_Pin, counter==5 || counter==6);
	 HAL_GPIO_WritePin(PIN_C_GPIO_Port, PIN_C_Pin, counter==2);
	 HAL_GPIO_WritePin(PIN_D_GPIO_Port, PIN_D_Pin, counter==1 || counter==4 || counter==7);
	 HAL_GPIO_WritePin(PIN_E_GPIO_Port, PIN_E_Pin, !(counter == 0 || counter == 2 || counter == 6 || counter == 8));
	 HAL_GPIO_WritePin(PIN_F_GPIO_Port, PIN_F_Pin, counter==1 || counter==2 || counter==3 || counter==7);
	 HAL_GPIO_WritePin(PIN_G_GPIO_Port, PIN_G_Pin, counter== 0 || counter==1 || counter==7);

 }

#elif EXERCISE == 5
 //CONFIGE TIMER FOR TRAFFIC LIGHT
 //NOTE: SUM OF TIME 3 LED OF TRAFFIC LIGHT MUST BE EQUAL SUM_TIME_LED
 //Real Time = Time x 10 ms and < 10 s
 //YELLOW_TIME + GREEN_TIME == RED_TIME_LED OTHER
#define SUM_TIME_LED 1700

#define TIME_LED_RED_1 900
#define TIME_LED_GREEN_1 600
#define TIME_LED_YELLOW_1 200

#define TIME_LED_RED_2 800
#define TIME_LED_GREEN_2 700
#define TIME_LED_YELLOW_2 200

#define LED_RED_1_Pin GPIO_PIN_0
#define LED_RED_1_GPIO_Port GPIOA
#define LED_GREEN_1_Pin GPIO_PIN_2
#define LED_GREEN_1_GPIO_Port GPIOA
#define LED_YELLOW_1_Pin GPIO_PIN_1
#define LED_YELLOW_1_GPIO_Port GPIOA
#define LED_RED_2_Pin GPIO_PIN_3
#define LED_RED_2_GPIO_Port GPIOA
#define LED_GREEN_2_Pin GPIO_PIN_5
#define LED_GREEN_2_GPIO_Port GPIOA
#define LED_YELLOW_2_Pin GPIO_PIN_4
#define LED_YELLOW_2_GPIO_Port GPIOA
#define PIN_A_1_Pin GPIO_PIN_6
#define PIN_A_1_GPIO_Port GPIOA
#define PIN_B_1_Pin GPIO_PIN_7
#define PIN_B_1_GPIO_Port GPIOA
#define PIN_A_2_Pin GPIO_PIN_0
#define PIN_A_2_GPIO_Port GPIOB
#define PIN_B_2_Pin GPIO_PIN_1
#define PIN_B_2_GPIO_Port GPIOB
#define PIN_C_2_Pin GPIO_PIN_2
#define PIN_C_2_GPIO_Port GPIOB
#define PIN_C_1_Pin GPIO_PIN_8
#define PIN_C_1_GPIO_Port GPIOA
#define PIN_D_1_Pin GPIO_PIN_9
#define PIN_D_1_GPIO_Port GPIOA
#define PIN_E_1_Pin GPIO_PIN_10
#define PIN_E_1_GPIO_Port GPIOA
#define PIN_F_1_Pin GPIO_PIN_11
#define PIN_F_1_GPIO_Port GPIOA
#define PIN_G_1_Pin GPIO_PIN_12
#define PIN_G_1_GPIO_Port GPIOA
#define PIN_D_2_Pin GPIO_PIN_3
#define PIN_D_2_GPIO_Port GPIOB
#define PIN_E_2_Pin GPIO_PIN_4
#define PIN_E_2_GPIO_Port GPIOB
#define PIN_F_2_Pin GPIO_PIN_5
#define PIN_F_2_GPIO_Port GPIOB
#define PIN_G_2_Pin GPIO_PIN_6
#define PIN_G_2_GPIO_Port GPIOB

 void display7SEG(int counter, int i){
	 if(counter >= 10 || counter < 0) return;
	 if(i == 1){
	 HAL_GPIO_WritePin(PIN_A_1_GPIO_Port, PIN_A_1_Pin, counter==1 || counter==4);
	 HAL_GPIO_WritePin(PIN_B_1_GPIO_Port, PIN_B_1_Pin, counter==5 || counter==6);
	 HAL_GPIO_WritePin(PIN_C_1_GPIO_Port, PIN_C_1_Pin, counter==2);
	 HAL_GPIO_WritePin(PIN_D_1_GPIO_Port, PIN_D_1_Pin, counter==1 || counter==4 || counter==7);
	 HAL_GPIO_WritePin(PIN_E_1_GPIO_Port, PIN_E_1_Pin, !(counter == 0 || counter == 2 || counter == 6 || counter == 8));
	 HAL_GPIO_WritePin(PIN_F_1_GPIO_Port, PIN_F_1_Pin, counter==1 || counter==2 || counter==3 || counter==7);
	 HAL_GPIO_WritePin(PIN_G_1_GPIO_Port, PIN_G_1_Pin, counter== 0 || counter==1 || counter==7);
	 }
	 else{
	 HAL_GPIO_WritePin(PIN_A_2_GPIO_Port, PIN_A_2_Pin, counter==1 || counter==4);
	 HAL_GPIO_WritePin(PIN_B_2_GPIO_Port, PIN_B_2_Pin, counter==5 || counter==6);
	 HAL_GPIO_WritePin(PIN_C_2_GPIO_Port, PIN_C_2_Pin, counter==2);
	 HAL_GPIO_WritePin(PIN_D_2_GPIO_Port, PIN_D_2_Pin, counter==1 || counter==4 || counter==7);
	 HAL_GPIO_WritePin(PIN_E_2_GPIO_Port, PIN_E_2_Pin, !(counter == 0 || counter == 2 || counter == 6 || counter == 8));
	 HAL_GPIO_WritePin(PIN_F_2_GPIO_Port, PIN_F_2_Pin, counter==1 || counter==2 || counter==3 || counter==7);
	 HAL_GPIO_WritePin(PIN_G_2_GPIO_Port, PIN_G_2_Pin, counter== 0 || counter==1 || counter==7);
	 }
 }
#elif EXERCISE == 6
#define PIN_1_Pin GPIO_PIN_0
#define PIN_1_GPIO_Port GPIOA
#define PIN_2_Pin GPIO_PIN_1
#define PIN_2_GPIO_Port GPIOA
#define PIN_3_Pin GPIO_PIN_2
#define PIN_3_GPIO_Port GPIOA
#define PIN_4_Pin GPIO_PIN_3
#define PIN_4_GPIO_Port GPIOA
#define PIN_5_Pin GPIO_PIN_4
#define PIN_5_GPIO_Port GPIOA
#define PIN_6_Pin GPIO_PIN_5
#define PIN_6_GPIO_Port GPIOA
#define PIN_7_Pin GPIO_PIN_6
#define PIN_7_GPIO_Port GPIOA
#define PIN_8_Pin GPIO_PIN_7
#define PIN_8_GPIO_Port GPIOA
#define PIN_9_Pin GPIO_PIN_8
#define PIN_9_GPIO_Port GPIOA
#define PIN_10_Pin GPIO_PIN_9
#define PIN_10_GPIO_Port GPIOA
#define PIN_11_Pin GPIO_PIN_10
#define PIN_11_GPIO_Port GPIOA
#define PIN_12_Pin GPIO_PIN_11
#define PIN_12_GPIO_Port GPIOA

//DENFINE FUNCTION

void  setNumberOnClock(int num){
if(num > 11 || num < 0) return;
if(num == 0){
	HAL_GPIO_WritePin(PIN_1_GPIO_Port, PIN_1_Pin, 0);
}
else if(num == 1){
	HAL_GPIO_WritePin(PIN_2_GPIO_Port, PIN_2_Pin, 0);
}
else if(num == 2){
	HAL_GPIO_WritePin(PIN_3_GPIO_Port, PIN_3_Pin, 0);
}
else if(num == 3){
	HAL_GPIO_WritePin(PIN_4_GPIO_Port, PIN_4_Pin, 0);
}
else if(num == 4){
	HAL_GPIO_WritePin(PIN_5_GPIO_Port, PIN_5_Pin, 0);
}
else if(num == 5){
	HAL_GPIO_WritePin(PIN_6_GPIO_Port, PIN_6_Pin, 0);
}
else if(num == 6){
	HAL_GPIO_WritePin(PIN_7_GPIO_Port, PIN_7_Pin, 0);
}
else if(num == 7){
	HAL_GPIO_WritePin(PIN_8_GPIO_Port, PIN_8_Pin, 0);
}
else if(num == 8){
	HAL_GPIO_WritePin(PIN_9_GPIO_Port, PIN_9_Pin, 0);
}
else if(num == 9){
	HAL_GPIO_WritePin(PIN_10_GPIO_Port, PIN_10_Pin, 0);
}
else if(num == 10){
	HAL_GPIO_WritePin(PIN_11_GPIO_Port, PIN_11_Pin, 0);
}
else if(num == 11){
	HAL_GPIO_WritePin(PIN_12_GPIO_Port, PIN_12_Pin, 0);
}
}
void clearNumberOnClock(int num){
	if(num > 11 || num < 0) return;
	if(num == 0){
		HAL_GPIO_WritePin(PIN_1_GPIO_Port, PIN_1_Pin, 1);
	}
	else if(num == 1){
		HAL_GPIO_WritePin(PIN_2_GPIO_Port, PIN_2_Pin, 1);
	}
	else if(num == 2){
		HAL_GPIO_WritePin(PIN_3_GPIO_Port, PIN_3_Pin, 1);
	}
	else if(num == 3){
		HAL_GPIO_WritePin(PIN_4_GPIO_Port, PIN_4_Pin, 1);
	}
	else if(num == 4){
		HAL_GPIO_WritePin(PIN_5_GPIO_Port, PIN_5_Pin, 1);
	}
	else if(num == 5){
		HAL_GPIO_WritePin(PIN_6_GPIO_Port, PIN_6_Pin, 1);
	}
	else if(num == 6){
		HAL_GPIO_WritePin(PIN_7_GPIO_Port, PIN_7_Pin, 1);
	}
	else if(num == 7){
		HAL_GPIO_WritePin(PIN_8_GPIO_Port, PIN_8_Pin, 1);
	}
	else if(num == 8){
		HAL_GPIO_WritePin(PIN_9_GPIO_Port, PIN_9_Pin, 1);
	}
	else if(num == 9){
		HAL_GPIO_WritePin(PIN_10_GPIO_Port, PIN_10_Pin, 1);
	}
	else if(num == 10){
		HAL_GPIO_WritePin(PIN_11_GPIO_Port, PIN_11_Pin, 1);
	}
	else if(num == 11){
		HAL_GPIO_WritePin(PIN_12_GPIO_Port, PIN_12_Pin, 1);
	}
}
void  clearAllClock(){
	HAL_GPIO_WritePin(PIN_1_GPIO_Port, PIN_1_Pin, 1);
	HAL_GPIO_WritePin(PIN_2_GPIO_Port, PIN_2_Pin, 1);
	HAL_GPIO_WritePin(PIN_3_GPIO_Port, PIN_3_Pin, 1);
	HAL_GPIO_WritePin(PIN_4_GPIO_Port, PIN_4_Pin, 1);
	HAL_GPIO_WritePin(PIN_5_GPIO_Port, PIN_5_Pin, 1);
	HAL_GPIO_WritePin(PIN_6_GPIO_Port, PIN_6_Pin, 1);
	HAL_GPIO_WritePin(PIN_7_GPIO_Port, PIN_7_Pin, 1);
	HAL_GPIO_WritePin(PIN_8_GPIO_Port, PIN_8_Pin, 1);
	HAL_GPIO_WritePin(PIN_9_GPIO_Port, PIN_9_Pin, 1);
	HAL_GPIO_WritePin(PIN_10_GPIO_Port, PIN_10_Pin, 1);
	HAL_GPIO_WritePin(PIN_11_GPIO_Port, PIN_11_Pin, 1);
	HAL_GPIO_WritePin(PIN_12_GPIO_Port, PIN_12_Pin, 1);
}
#elif EXERCISE == 7

#elif EXERCISE == 8

#elif EXERCISE == 9

#elif EXERCISE == 10
//IF ALL PORT OF PIN 1-12 SAME AND NOT USE EXCEPT TASK
void  setNumberOnClock(int num){
if(num > 11 || num < 0) return;
HAL_GPIO_WritePin(PIN_1_GPIO_Port, 1<<num, 0);
}
void clearNumberOnClock(int num){
	if(num > 11 || num < 0) return;
	HAL_GPIO_WritePin(PIN_1_GPIO_Port, 1<<num, 1);
}
void  clearAllClock(){
	 uint16_t temp = 15;
HAL_GPIO_WritePin(PIN_1_GPIO_Port, ~(temp<<12) , 1);
}
#endif
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  /* USER CODE BEGIN 2 */
#if EXERCISE == 1
  int32_t counter = 400;
  int8_t state = -1;
#elif EXERCISE == 2
  int32_t counter = 1000;
  int8_t state = -1;
#elif EXERCISE == 3
  int32_t counter = SUM_TIME_LED;
  int8_t state = -1;
#elif EXERCISE == 4
  int32_t counter = 100;
  uint8_t state = 0;
  uint32_t counter_7LED = 100;
#elif EXERCISE == 5
  int32_t counter = SUM_TIME_LED;
  int8_t state = -1;
  int32_t counter_7LED = 0;
#elif EXERCISE == 6
  int8_t hour = 1;
  int8_t minute = 1;
  int8_t second = 1;
  int32_t counter = 50;
#elif EXERCISE == 7

#elif EXERCISE == 8

#elif EXERCISE == 9

#elif EXERCISE == 10

#endif
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
#if EXERCISE == 1
	  if(counter == 400 && state != 0){
	  		  HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, 1);
	  		  HAL_GPIO_WritePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin, 0);
	  		  state = 0;
	  }
	  else if(counter == 200 && state != 1){
	  		  HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, 0);
	  		  HAL_GPIO_WritePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin, 1);
	  		  state = 1;
	  }
	  else if(counter <= 1)
	  		  counter = 401;
	  counter--;
	  HAL_Delay(10);
#elif EXERCISE == 2
	  if(counter == 1000 && state != 0){
	  		  HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, 0);
	  		  HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, 1);
	  		  HAL_GPIO_WritePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin, 1);
	  		  state = 0;
	  }
	  else if(counter == 500 && state != 1){
	  		  HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, 1);
	  		  HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, 0);
	  		  HAL_GPIO_WritePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin, 1);
	  		  state = 1;
	  }
	  else if(counter == 200 && state != 2){
  		  	  HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, 1);
  		  	  HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, 1);
  		  	  HAL_GPIO_WritePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin, 0);
  		  	  state = 2;
	  }
	  else if(counter <= 1)
	  		  counter = 1001;
	  counter--;
	  HAL_Delay(10);
#elif EXERCISE == 3
	  if(counter == SUM_TIME_LED && state != 0){
		  		  HAL_GPIO_WritePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin, 0);
		  		  HAL_GPIO_WritePin(LED_GREEN_1_GPIO_Port, LED_GREEN_1_Pin, 1);
		  		  HAL_GPIO_WritePin(LED_YELLOW_1_GPIO_Port, LED_YELLOW_1_Pin, 1);
		  	  	  HAL_GPIO_WritePin(LED_RED_2_GPIO_Port, LED_RED_2_Pin, 1);
				  HAL_GPIO_WritePin(LED_GREEN_2_GPIO_Port, LED_GREEN_2_Pin, 0);
				  HAL_GPIO_WritePin(LED_YELLOW_2_GPIO_Port, LED_YELLOW_2_Pin, 1);
	  	  		  state = 0;
	  	  }
	  else if(counter == SUM_TIME_LED - TIME_LED_GREEN_2 && state != 1){
  		  	  	  HAL_GPIO_WritePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin, 0);
  		  	  	  HAL_GPIO_WritePin(LED_GREEN_1_GPIO_Port, LED_GREEN_1_Pin, 1);
  		  	  	  HAL_GPIO_WritePin(LED_YELLOW_1_GPIO_Port, LED_YELLOW_1_Pin, 1);
  	  	  	  	  HAL_GPIO_WritePin(LED_RED_2_GPIO_Port, LED_RED_2_Pin, 1);
  	  	  	  	  HAL_GPIO_WritePin(LED_GREEN_2_GPIO_Port, LED_GREEN_2_Pin, 1);
  	  	  	  	  HAL_GPIO_WritePin(LED_YELLOW_2_GPIO_Port, LED_YELLOW_2_Pin, 0);
  	  	  	  	  state = 1;
	  }
	  else if(counter == TIME_LED_RED_2 && state != 2){
	  		  		  HAL_GPIO_WritePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin, 1);
	  		  		  HAL_GPIO_WritePin(LED_GREEN_1_GPIO_Port, LED_GREEN_1_Pin, 0);
	  		  		  HAL_GPIO_WritePin(LED_YELLOW_1_GPIO_Port, LED_YELLOW_1_Pin, 1);
	  	  	  	  	  HAL_GPIO_WritePin(LED_RED_2_GPIO_Port, LED_RED_2_Pin, 0);
	  	  	  	  	  HAL_GPIO_WritePin(LED_GREEN_2_GPIO_Port, LED_GREEN_2_Pin, 1);
	  	  	  	  	  HAL_GPIO_WritePin(LED_YELLOW_2_GPIO_Port, LED_YELLOW_2_Pin, 1);
  	  		  		  state = 2;
	  	  }
	  else if(counter == TIME_LED_YELLOW_1 && state != 3){
		  		   	  HAL_GPIO_WritePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin, 1);
		  		   	  HAL_GPIO_WritePin(LED_GREEN_1_GPIO_Port, LED_GREEN_1_Pin, 1);
		  		   	  HAL_GPIO_WritePin(LED_YELLOW_1_GPIO_Port, LED_YELLOW_1_Pin, 0);
	  	  	  	  	  HAL_GPIO_WritePin(LED_RED_2_GPIO_Port, LED_RED_2_Pin, 0);
	  	  	  	  	  HAL_GPIO_WritePin(LED_GREEN_2_GPIO_Port, LED_GREEN_2_Pin, 1);
	  	  	  	  	  HAL_GPIO_WritePin(LED_YELLOW_2_GPIO_Port, LED_YELLOW_2_Pin, 1);
		  		   	  state = 3;
	  	  }
	  else if(counter <= 1)
	  	  		  counter = SUM_TIME_LED+1;
	  	  counter--;
	  	  HAL_Delay(10);
#elif EXERCISE == 4
		if(state >= 10) state = 0;
	  	if(counter <= 0){
		  	 display7SEG(state++);
		  	 counter = 100;
	  	}
	  	counter--;
	  	HAL_Delay(10);
#elif EXERCISE == 5
		  if(counter == SUM_TIME_LED && state != 0){
			  		  HAL_GPIO_WritePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin, 0);
			  		  HAL_GPIO_WritePin(LED_GREEN_1_GPIO_Port, LED_GREEN_1_Pin, 1);
			  		  HAL_GPIO_WritePin(LED_YELLOW_1_GPIO_Port, LED_YELLOW_1_Pin, 1);
			  	  	  HAL_GPIO_WritePin(LED_RED_2_GPIO_Port, LED_RED_2_Pin, 1);
					  HAL_GPIO_WritePin(LED_GREEN_2_GPIO_Port, LED_GREEN_2_Pin, 0);
					  HAL_GPIO_WritePin(LED_YELLOW_2_GPIO_Port, LED_YELLOW_2_Pin, 1);
		  	  		  state = 0;
		  	  }
		  else if(counter == SUM_TIME_LED - TIME_LED_GREEN_2 && state != 1){
	  		  	  	  HAL_GPIO_WritePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin, 0);
	  		  	  	  HAL_GPIO_WritePin(LED_GREEN_1_GPIO_Port, LED_GREEN_1_Pin, 1);
	  		  	  	  HAL_GPIO_WritePin(LED_YELLOW_1_GPIO_Port, LED_YELLOW_1_Pin, 1);
	  	  	  	  	  HAL_GPIO_WritePin(LED_RED_2_GPIO_Port, LED_RED_2_Pin, 1);
	  	  	  	  	  HAL_GPIO_WritePin(LED_GREEN_2_GPIO_Port, LED_GREEN_2_Pin, 1);
	  	  	  	  	  HAL_GPIO_WritePin(LED_YELLOW_2_GPIO_Port, LED_YELLOW_2_Pin, 0);
	  	  	  	  	  state = 1;
		  }
		  else if(counter == TIME_LED_RED_2 && state != 2){
		  		  		  HAL_GPIO_WritePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin, 1);
		  		  		  HAL_GPIO_WritePin(LED_GREEN_1_GPIO_Port, LED_GREEN_1_Pin, 0);
		  		  		  HAL_GPIO_WritePin(LED_YELLOW_1_GPIO_Port, LED_YELLOW_1_Pin, 1);
		  	  	  	  	  HAL_GPIO_WritePin(LED_RED_2_GPIO_Port, LED_RED_2_Pin, 0);
		  	  	  	  	  HAL_GPIO_WritePin(LED_GREEN_2_GPIO_Port, LED_GREEN_2_Pin, 1);
		  	  	  	  	  HAL_GPIO_WritePin(LED_YELLOW_2_GPIO_Port, LED_YELLOW_2_Pin, 1);
	  	  		  		  state = 2;
		  	  }
		  else if(counter == TIME_LED_YELLOW_1 && state != 3){
			  		   	  HAL_GPIO_WritePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin, 1);
			  		   	  HAL_GPIO_WritePin(LED_GREEN_1_GPIO_Port, LED_GREEN_1_Pin, 1);
			  		   	  HAL_GPIO_WritePin(LED_YELLOW_1_GPIO_Port, LED_YELLOW_1_Pin, 0);
		  	  	  	  	  HAL_GPIO_WritePin(LED_RED_2_GPIO_Port, LED_RED_2_Pin, 0);
		  	  	  	  	  HAL_GPIO_WritePin(LED_GREEN_2_GPIO_Port, LED_GREEN_2_Pin, 1);
		  	  	  	  	  HAL_GPIO_WritePin(LED_YELLOW_2_GPIO_Port, LED_YELLOW_2_Pin, 1);
			  		   	  state = 3;
		  	  }
		  else if(counter <= 1)
		  	  		  counter = SUM_TIME_LED+1;
//CONTROL 7 7SEG-LED
		  	if(counter_7LED <= 0){
		  		if(state == 0){
				  	display7SEG((TIME_LED_RED_1 - (SUM_TIME_LED - counter))/100, 1);
				  	display7SEG((TIME_LED_GREEN_2 - (SUM_TIME_LED - counter))/100, 2);
		  		}
		  		else if(state == 1){
				  	display7SEG((TIME_LED_RED_1 - (SUM_TIME_LED - counter))/100, 1);
				  	display7SEG((TIME_LED_YELLOW_2 - (SUM_TIME_LED - counter - TIME_LED_GREEN_2))/100, 2);
		  		}
		  		else if(state == 2){
				  	display7SEG((TIME_LED_GREEN_1 - (SUM_TIME_LED - counter - TIME_LED_RED_1))/100, 1);
				  	display7SEG(counter/100, 2);
		  		}
		  		else if(state == 3){
		  			display7SEG(counter/100, 1);
		  			display7SEG(counter/100, 2);
		  		}
			  	 counter_7LED = 100;
		  	}
		  	  counter_7LED--;
		  	  counter--;
		  	  HAL_Delay(10);
#elif EXERCISE == 6
		  	  if(counter <= 0){
		  		  second++;
		  		  clearAllClock();
			  	  if(second > 12){
			  		  minute++;
				  	  if(minute > 12){
				  		  hour++;
					  	  if(hour > 12){
					  		  hour = 1;
					  	  }
				  		  minute = 1;
				  	  }
			  		  second = 1;
			  	  }
			  	  setNumberOnClock(second-1);
			  	  setNumberOnClock(minute-1);
			  	  setNumberOnClock(hour-1);
		  		  counter = 50;
		  	  }
counter--;
HAL_Delay(10);
#elif EXERCISE == 7

#elif EXERCISE == 8

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
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();

/* USER CODE BEGIN MX_GPIO_Init_2 */
#if EXERCISE == 1
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LED_RED_Pin|LED_YELLOW_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : LED_RED_Pin LED_GREEN_Pin */
  GPIO_InitStruct.Pin = LED_RED_Pin|LED_YELLOW_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

#elif EXERCISE == 2
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOA, LED_RED_Pin|LED_GREEN_Pin|LED_YELLOW_Pin, GPIO_PIN_RESET);

    /*Configure GPIO pins : LED_RED_Pin LED_GREEN_Pin LED_YELLOW_Pin */
    GPIO_InitStruct.Pin = LED_RED_Pin|LED_GREEN_Pin|LED_YELLOW_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
#elif EXERCISE == 3
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOB_CLK_ENABLE();
    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOA, LED_RED_1_Pin|LED_GREEN_1_Pin|LED_YELLOW_1_Pin, GPIO_PIN_RESET);

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOB, LED_RED_2_Pin|LED_GREEN_2_Pin|LED_YELLOW_2_Pin, GPIO_PIN_RESET);

    /*Configure GPIO pins : LED_RED_1_Pin LED_GREEN_1_Pin LED_YELLOW_1_Pin */
    GPIO_InitStruct.Pin = LED_RED_1_Pin|LED_GREEN_1_Pin|LED_YELLOW_1_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /*Configure GPIO pins : LED_RED_2_Pin LED_GREEN_2_Pin LED_YELLOW_2_Pin */
    GPIO_InitStruct.Pin = LED_RED_2_Pin|LED_GREEN_2_Pin|LED_YELLOW_2_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

#elif EXERCISE == 4
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    /* USER CODE BEGIN MX_GPIO_Init_1 */
    /* USER CODE END MX_GPIO_Init_1 */

      /* GPIO Ports Clock Enable */
      __HAL_RCC_GPIOB_CLK_ENABLE();

      /*Configure GPIO pin Output Level */
      HAL_GPIO_WritePin(GPIOB, PIN_A_Pin|PIN_B_Pin|PIN_C_Pin|PIN_D_Pin
                              |PIN_E_Pin|PIN_F_Pin|PIN_G_Pin, GPIO_PIN_RESET);

      /*Configure GPIO pins : PIN_A_Pin PIN_B_Pin PIN_C_Pin PIN_D_Pin
                               PIN_E_Pin PIN_F_Pin PIN_G_Pin */
      GPIO_InitStruct.Pin = PIN_A_Pin|PIN_B_Pin|PIN_C_Pin|PIN_D_Pin
                              |PIN_E_Pin|PIN_F_Pin|PIN_G_Pin;
      GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
      GPIO_InitStruct.Pull = GPIO_NOPULL;
      GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
      HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
#elif EXERCISE == 5
      GPIO_InitTypeDef GPIO_InitStruct = {0};
    /* USER CODE BEGIN MX_GPIO_Init_1 */
    /* USER CODE END MX_GPIO_Init_1 */

      /* GPIO Ports Clock Enable */
      __HAL_RCC_GPIOB_CLK_ENABLE();

      /*Configure GPIO pin Output Level */
      HAL_GPIO_WritePin(GPIOA, LED_RED_1_Pin|LED_GREEN_1_Pin|LED_YELLOW_1_Pin|LED_RED_2_Pin
                              |LED_GREEN_2_Pin|LED_YELLOW_2_Pin|PIN_A_1_Pin|PIN_B_1_Pin
                              |PIN_C_1_Pin|PIN_D_1_Pin|PIN_E_1_Pin|PIN_F_1_Pin
                              |PIN_G_1_Pin, GPIO_PIN_RESET);

      /*Configure GPIO pin Output Level */
      HAL_GPIO_WritePin(GPIOB, PIN_A_2_Pin|PIN_B_2_Pin|PIN_C_2_Pin|PIN_D_2_Pin
                              |PIN_E_2_Pin|PIN_F_2_Pin|PIN_G_2_Pin, GPIO_PIN_RESET);

      /*Configure GPIO pins : LED_RED_1_Pin LED_GREEN_1_Pin LED_YELLOW_1_Pin LED_RED_2_Pin
                               LED_GREEN_2_Pin LED_YELLOW_2_Pin PIN_A_1_Pin PIN_B_1_Pin
                               PIN_C_1_Pin PIN_D_1_Pin PIN_E_1_Pin PIN_F_1_Pin
                               PIN_G_1_Pin */
      GPIO_InitStruct.Pin = LED_RED_1_Pin|LED_GREEN_1_Pin|LED_YELLOW_1_Pin|LED_RED_2_Pin
                              |LED_GREEN_2_Pin|LED_YELLOW_2_Pin|PIN_A_1_Pin|PIN_B_1_Pin
                              |PIN_C_1_Pin|PIN_D_1_Pin|PIN_E_1_Pin|PIN_F_1_Pin
                              |PIN_G_1_Pin;
      GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
      GPIO_InitStruct.Pull = GPIO_NOPULL;
      GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
      HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

      /*Configure GPIO pins : PIN_A_2_Pin PIN_B_2_Pin PIN_C_2_Pin PIN_D_2_Pin
                               PIN_E_2_Pin PIN_F_2_Pin PIN_G_2_Pin */
      GPIO_InitStruct.Pin = PIN_A_2_Pin|PIN_B_2_Pin|PIN_C_2_Pin|PIN_D_2_Pin
                              |PIN_E_2_Pin|PIN_F_2_Pin|PIN_G_2_Pin;
      GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
      GPIO_InitStruct.Pull = GPIO_NOPULL;
      GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
      HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
#elif EXERCISE == 6
      GPIO_InitTypeDef GPIO_InitStruct = {0};
    /* USER CODE BEGIN MX_GPIO_Init_1 */
    /* USER CODE END MX_GPIO_Init_1 */

      /* GPIO Ports Clock Enable */

      /*Configure GPIO pin Output Level */
      HAL_GPIO_WritePin(GPIOA, PIN_1_Pin|PIN_2_Pin|PIN_3_Pin|PIN_4_Pin
                              |PIN_5_Pin|PIN_6_Pin|PIN_7_Pin|PIN_8_Pin
                              |PIN_9_Pin|PIN_10_Pin|PIN_11_Pin|PIN_12_Pin, GPIO_PIN_RESET);

      /*Configure GPIO pins : PIN_1_Pin PIN_2_Pin PIN_3_Pin PIN_4_Pin
                               PIN_5_Pin PIN_6_Pin PIN_7_Pin PIN_8_Pin
                               PIN_9_Pin PIN_10_Pin PIN_11_Pin PIN_12_Pin */
      GPIO_InitStruct.Pin = PIN_1_Pin|PIN_2_Pin|PIN_3_Pin|PIN_4_Pin
                              |PIN_5_Pin|PIN_6_Pin|PIN_7_Pin|PIN_8_Pin
                              |PIN_9_Pin|PIN_10_Pin|PIN_11_Pin|PIN_12_Pin;
      GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
      GPIO_InitStruct.Pull = GPIO_NOPULL;
      GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
      HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
#elif EXERCISE == 7

#elif EXERCISE == 8

#elif EXERCISE == 9

#elif EXERCISE == 10

#endif

/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

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
