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
#include "timer_driver.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
#define EXERCISE 10
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

//
#if EXERCISE == 1

#elif EXERCISE == 2

#elif EXERCISE == 3

#elif EXERCISE == 4

#elif EXERCISE == 5
#define TIME_SWITCH 25
//(x10 ms)
int counter = TIME_SWITCH;
int time_2led = 25;
int hour = 15, minute = 59, second = 50;

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
  setTimer(0, 1000);
#elif EXERCISE == 7
  setTimer(0, 1000); //RED_LED
  setTimer(1, 7); //CLOCK HOUR_MINUTE_SECOND
  setTimer(2, 250); //DISLAY 7 - SEG LED
  setTimer(3, 500);
#elif EXERCISE == 8

#elif EXERCISE == 9
  setTimer(0, 10);
#elif EXERCISE == 10
  setTimer(0, 100);
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
	  if(istimer_flag(0) == 1){
	   HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
	   setTimer(0,2000);
	   }
#elif EXERCISE == 7
	  if(istimer_flag(0) == 1){
		   HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
		   setTimer(0, 2000);
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
		  setTimer(1, 1000);
	  }
	  if(istimer_flag(2) == 1){
		  update7SEG(index_led++);
		  if(index_led > 3) index_led = 0;
		  setTimer(2, 250);
	  }
	  if(istimer_flag(3) == 1){
		  HAL_GPIO_TogglePin(DOT_GPIO_Port, DOT_Pin);
		  setTimer(3, 1000);
	  }
#elif EXERCISE == 8

#elif EXERCISE == 9
	  if(istimer_flag(0) == 1){
		  updateLEDMatrix(index_led_matrix, matrix_buffer[index_led_matrix]);
		  index_led_matrix++;
		  if(index_led_matrix > 7) index_led_matrix = 0;
		  setTimer(0, 10);
	  }
#elif EXERCISE == 10
	  if(istimer_flag(0) == 1){
		  matrix_buffer[index_led_matrix] = matrix_buffer[index_led_matrix]<<1|matrix_buffer[index_led_matrix]>>7;
		  updateLEDMatrix(index_led_matrix--);
		  if(index_led_matrix < 0) {index_led_matrix = 7;}
		  setTimer(0, 10);
	  }
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

}
#elif EXERCISE == 9
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
timer_run();
}
#elif EXERCISE == 10
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
timer_run();
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
