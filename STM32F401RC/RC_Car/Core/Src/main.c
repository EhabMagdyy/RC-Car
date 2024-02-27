/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @author         : Ehab Magdy Abdallah
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "dcmotor_lcfg.h"
#include "ultrasonic_lcfg.h"
#include "buzzer_lcfg.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
volatile uint8_t ultrasonic_reading_finished_flag = 0;
static volatile uint8_t is_firt_captured = 0;
static volatile uint32_t IC_Val1 = 0;
static volatile uint32_t IC_Val2 = 0;
static volatile uint32_t IC_Difference = 0;
uint16_t distance = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void adjust_PWM_dutyCycle(TIM_HandleTypeDef* pwmHandle, uint32_t pwmChannel, float dutyCycle)
{

    // Calculate the new pulse width based on the duty cycle percentage
    uint32_t maxCCR = pwmHandle->Instance->ARR;
    uint32_t newCCR = (uint32_t)((dutyCycle / 100.0f) * maxCCR);

    // Update the CCR value for the specified channel
    __HAL_TIM_SET_COMPARE(pwmHandle, pwmChannel, newCCR);
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	/* Capture rising edge */
	if(0 == is_firt_captured)
	{
		IC_Val1 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
		is_firt_captured = 1;
		__HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_FALLING);
		ultrasonic_reading_finished_flag = 0;
	}
	/* Capture falling edge */
	else if(1 == is_firt_captured)
	{
		IC_Val2 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
		__HAL_TIM_SET_COUNTER(htim, 0);

		if(IC_Val2 > IC_Val1)
		{
			IC_Difference = IC_Val2 - IC_Val1;
		}
		else if(IC_Val1 > IC_Val2)
		{
			IC_Difference = (0xFFFF - IC_Val1) + IC_Val2;
		}

		distance = IC_Difference * 0.017;

		is_firt_captured = 0;
		__HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_RISING);
		__HAL_TIM_DISABLE_IT(&htim4, TIM_IT_CC1);
		ultrasonic_reading_finished_flag = 1;
	}
	else{ /* Nothing */ }
}

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
	uint8_t bt_value = 0;
	uint8_t last_bt_value = 0;
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
  MX_USART1_UART_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
  adjust_PWM_dutyCycle(&htim3, TIM_CHANNEL_1, 50);
  HAL_TIM_IC_Start_IT(&htim4, TIM_CHANNEL_1);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  if(ultrasonic_reading_finished_flag)
	  {
		  Ultrasonic_Get_Distance(&ultrasonic);
		  HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
	  }
	  else{/* Nothing */}

	  HAL_UART_Receive(&huart1, (uint8_t*)&bt_value, 1, 20);

	  if(bt_value){ last_bt_value = bt_value; }
	  else{ bt_value = last_bt_value; }

	  switch(bt_value)
	  {
		  case 'F':
			  if(20 > distance && 0 < distance)
			  {
				  HAL_GPIO_WritePin(Buzzerl_GPIO_Port, Buzzerl_Pin, GPIO_PIN_SET);
				  RC_Car_Stop();
			  }
			  else
			  {
				  HAL_GPIO_WritePin(Buzzerl_GPIO_Port, Buzzerl_Pin, GPIO_PIN_RESET);
				  RC_Car_Move_Forward();
			  }
			  break;

		  case 'B':
			  if(20 <= distance)
			  {
				  HAL_GPIO_WritePin(Buzzerl_GPIO_Port, Buzzerl_Pin, GPIO_PIN_RESET);
			  }

			  RC_Car_Move_Backward();
			  break;

		  case 'R':
			  if(20 <= distance)
			  {
				  HAL_GPIO_WritePin(Buzzerl_GPIO_Port, Buzzerl_Pin, GPIO_PIN_RESET);
			  }

			  RC_Car_Move_Right();
			  break;

		  case 'L':
			  if(20 <= distance)
			  {
				  HAL_GPIO_WritePin(Buzzerl_GPIO_Port, Buzzerl_Pin, GPIO_PIN_RESET);
			  }

			  RC_Car_Move_Left();
			  break;

		  case 'S':
			  RC_Car_Stop();
			  break;

		  case '1':
			  RC_Car_Stop();
			  adjust_PWM_dutyCycle(&htim3, TIM_CHANNEL_1, 50);
			  break;

		  case '2':
			  RC_Car_Stop();
			  adjust_PWM_dutyCycle(&htim3, TIM_CHANNEL_1, 65);
			  break;

		  case '3':
			  RC_Car_Stop();
			  adjust_PWM_dutyCycle(&htim3, TIM_CHANNEL_1, 80);
			  break;

		  case '4':
			  RC_Car_Stop();
			  adjust_PWM_dutyCycle(&htim3, TIM_CHANNEL_1, 100);
			  break;

		  default:
			  break;
	  }

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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 84;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void RC_Car_Move_Forward(void)
{
	DCMotor_Forward(&motor_left);
	DCMotor_Forward(&motor_right);
}

void RC_Car_Move_Backward(void)
{
	DCMotor_Backward(&motor_left);
	DCMotor_Backward(&motor_right);
}

void RC_Car_Move_Right(void)
{
	DCMotor_Forward(&motor_left);
	DCMotor_Backward(&motor_right);
}

void RC_Car_Move_Left(void)
{
	DCMotor_Backward(&motor_left);
	DCMotor_Forward(&motor_right);
}

void RC_Car_Stop(void)
{
	DCMotor_Stop(&motor_left);
	DCMotor_Stop(&motor_right);
}
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
