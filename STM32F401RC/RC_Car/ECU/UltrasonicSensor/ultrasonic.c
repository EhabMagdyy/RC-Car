/*****************************************************************************************
 ****************** @file           : ultrasonic.c		              ********************
 ****************** @author         : Ehab Magdy Abdallah             ********************
 ****************** @brief          : interface Ultrasonic Driver     ********************
******************************************************************************************/

/******************************          Includes           ******************************/
#include "ultrasonic.h"
//#include "stm32f4xx_hal_tim.h"

extern TIM_HandleTypeDef htim4;

/******************************      Software interfaces      ******************************/

static void Delay_10US(void)
{
	__HAL_TIM_SET_COUNTER(&htim4, 0);
	while(__HAL_TIM_GET_COUNTER(&htim4) < 5);
}

void Ultrasonic_Get_Distance(const ultrasonic_t *ultrasonic)
{
	/* Send Trigger Signal to the Ultrasonic Trigger Pin */
	HAL_GPIO_WritePin(ultrasonic->Ultrasonic_Port, ultrasonic->Ultrasonic_Trigger_Pin, GPIO_PIN_SET);
	Delay_10US();
	HAL_GPIO_WritePin(ultrasonic->Ultrasonic_Port, ultrasonic->Ultrasonic_Trigger_Pin, GPIO_PIN_RESET);

	__HAL_TIM_ENABLE_IT(&htim4, TIM_IT_CC1);
}
