/*****************************************************************************************
 ****************** @file           : buzzer.c				      	  ********************
 ****************** @author         : Ehab Magdy Abdallah             ********************
 ****************** @brief          : interface file buzzer Driver	  ********************
******************************************************************************************/

/******************************          Includes           ******************************/
#include "buzzer.h"
#include "stddef.h"

void buzzer_On(const buzzer_t* buzzer)
{
	if(NULL != buzzer)
	{
		HAL_GPIO_WritePin(buzzer->Buzzer_Port, buzzer->Buzzer_Pin, GPIO_PIN_SET);
	}
	else{ /* Do Nothing */ }
}

void buzzer_Off(const buzzer_t* buzzer)
{
	if(NULL != buzzer)
	{
		HAL_GPIO_WritePin(buzzer->Buzzer_Port, buzzer->Buzzer_Pin, GPIO_PIN_RESET);
	}
	else{ /* Do Nothing */ }
}

