/*
 * task_accelerometer.h
 *
 *  Created on: Nov 25, 2020
 *  Authors: Michael Sexton and Jack Bybel
 *
 */

#ifndef TASK_ACCELEROMETER_H_
#define TASK_ACCELEROMETER_H_

#include "main.h"

extern TaskHandle_t Task_Accelerometer_Handle;
extern TaskHandle_t Task_Accelerometer_Timer_Handle;

/******************************************************************************
* Initializes all hardware for the accelerometer
******************************************************************************/
 void Task_Accelerometer_Init(void);

/******************************************************************************
* Used to start an ADC14 Conversion
******************************************************************************/
void Task_Accelerometer_Timer(void *pvParameters);


/******************************************************************************
* Examines the ADC data from the joystick on the MKII
******************************************************************************/
void Task_Accelerometer(void *pvParameters);



#endif /* TASK_ACCELEROMETER_H_ */
