/*
 * task_accelerometer.h
 *
 *  Created on: Nov 25, 2020
 *  Authors: Michael Sexton and John Bybel
 *
 */

#ifndef TASK_ACCELEROMETER_H_
#define TASK_ACCELEROMETER_H_

#include "main.h"

extern TaskHandle_t Task_Accelerometer_Handle;
extern TaskHandle_t Task_Accelerometer_Timer_Handle;

/******************************************************************************
* Configure the IO pins for BOTH the X and Y directions of the analog
* joystick.  The X direction should be configured to place the results in
* MEM[0].  The Y direction should be configured to place the results in MEM[1].
*
* After BOTH analog signals have finished being converted, a SINGLE interrupt
* should be generated.
*
* Parameters
*      None
* Returns
*      None
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
