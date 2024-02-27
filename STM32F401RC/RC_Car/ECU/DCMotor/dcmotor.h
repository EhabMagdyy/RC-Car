/*****************************************************************************************
 ****************** @file           : dcmotor.h		         	      ********************
 ****************** @author         : Ehab Magdy Abdallah             ********************
 ****************** @brief          : interface file DC Motor         ********************
******************************************************************************************/

#ifndef DCMOTOR_DCMOTOR_H_
#define DCMOTOR_DCMOTOR_H_

/******************************          Includes           ******************************/
#include "stm32f4xx_hal.h"

/******************************   Data Types Decelerations  ******************************/
typedef struct
{
	GPIO_TypeDef*     Motor1_Port;
	uint16_t		  Motor1_Pin;
	GPIO_TypeDef*     Motor2_Port;
	uint16_t		  Motor2_Pin;
} dcmotor_t;

/******************************      Software intefaces      ******************************/
void DCMotor_Forward(const dcmotor_t* dcmotor);
void DCMotor_Backward(const dcmotor_t* dcmotor);
void DCMotor_Stop(const dcmotor_t* dcmotor);

#endif /* DCMOTOR_DCMOTOR_H_ */
