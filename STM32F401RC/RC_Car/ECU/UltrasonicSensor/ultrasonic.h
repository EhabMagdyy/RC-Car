/*****************************************************************************************
 ****************** @file           : ultrasonic.h		              ********************
 ****************** @author         : Ehab Magdy Abdallah             ********************
 ****************** @brief          : interface Ultrasonic Driver     ********************
******************************************************************************************/


#ifndef ULTRASONICSENSOR_ULTRASONIC_H_
#define ULTRASONICSENSOR_ULTRASONIC_H_

/******************************          Includes           ******************************/
#include "stm32f4xx_hal.h"

/******************************   Data Types Decelerations  ******************************/
typedef struct
{
	GPIO_TypeDef*     Ultrasonic_Port;
	uint16_t		  Ultrasonic_Trigger_Pin;
	uint16_t		  Ultrasonic_Echo_Pin;
} ultrasonic_t;

/******************************      Software intefaces      ******************************/
void Ultrasonic_Get_Distance(const ultrasonic_t *ultrasonic);

#endif /* ULTRASONICSENSOR_ULTRASONIC_H_ */
