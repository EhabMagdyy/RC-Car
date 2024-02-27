/*****************************************************************************************
 ****************** @file           : dcmotor.c		         	      ********************
 ****************** @author         : Ehab Magdy Abdallah             ********************
 ****************** @brief          : interface file DC Motor         ********************
******************************************************************************************/

#include "dcmotor.h"

/******************************      Software intefaces      ******************************/
void DCMotor_Forward(const dcmotor_t* dcmotor)
{
	if(NULL != dcmotor)
	{
		HAL_GPIO_WritePin(dcmotor->Motor1_Port, dcmotor->Motor1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(dcmotor->Motor2_Port, dcmotor->Motor2_Pin, GPIO_PIN_RESET);
	}
	else { /* Do Nothing */ }
}

void DCMotor_Backward(const dcmotor_t* dcmotor)
{
	if(NULL != dcmotor)
	{
		HAL_GPIO_WritePin(dcmotor->Motor1_Port, dcmotor->Motor1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(dcmotor->Motor2_Port, dcmotor->Motor2_Pin, GPIO_PIN_SET);
	}
	else { /* Do Nothing */ }
}

void DCMotor_Stop(const dcmotor_t* dcmotor)
{
	if(NULL != dcmotor)
	{
		HAL_GPIO_WritePin(dcmotor->Motor1_Port, dcmotor->Motor1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(dcmotor->Motor2_Port, dcmotor->Motor2_Pin, GPIO_PIN_RESET);
	}
	else { /* Do Nothing */ }
}
