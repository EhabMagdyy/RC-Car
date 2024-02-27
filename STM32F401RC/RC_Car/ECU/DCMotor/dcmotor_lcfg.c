/*****************************************************************************************
 ****************** @file           : dcmotor_cfg.c		         	  ********************
 ****************** @author         : Ehab Magdy Abdallah             ********************
 ****************** @brief          : Configuration file DC Motor     ********************
******************************************************************************************/

#include "dcmotor.h"

const dcmotor_t motor_left = {.Motor1_Port = GPIOA, .Motor1_Pin = GPIO_PIN_0,
						   .Motor2_Port = GPIOA, .Motor2_Pin = GPIO_PIN_1};
const dcmotor_t motor_right = {.Motor1_Port = GPIOA, .Motor1_Pin = GPIO_PIN_2,
						   .Motor2_Port = GPIOA, .Motor2_Pin = GPIO_PIN_3};
