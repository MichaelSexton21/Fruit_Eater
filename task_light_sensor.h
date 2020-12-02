/*
 * task_accelerometer.h
 *
 *  Created on: Nov 25, 2020
 *  Authors: Michael Sexton and John Bybel
 *
 */

#ifndef TASK_LIGHT_SENSOR_H_
#define TASK_LIGHT_SENSOR_H_

#include "main.h"
#include "i2c.h"

#define I2C_OPT3001_ADDRESS 0x44
#define I2C_OPT3001_RESULT_REG 0x00
#define I2C_OPT3001_CONFIG_REG 0x01

/* CONFIGURATION REGISTER SETTINGS */
#define OPT3001_RST              0x8000
#define OPT3001_POWER_DOWN       0x0000
#define OPT3001_POWER_UP         0x7000
#define OPT3001_CR_4             0x0000
#define OPT3001_CR_2             0x0200
#define OPT3001_CR_1             0x0400
#define OPT3001_CR_0_5           0x0600
#define OPT3001_CR_0_25          0x0800
#define OPT3001_EN               0x0100
#define OPT3001_DRDY             0x0080

extern TaskHandle_t Task_Light_Sensor_Handle;
extern TaskHandle_t Task_Light_Sensor_Timer_Handle;

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
 void Task_Light_Sensor_Init(void);


 void Task_Light_Sensor_Timer(void *pvParameters);

/******************************************************************************
* Examines the ADC data from the joystick on the MKII
******************************************************************************/
void Task_Light_Sensor(void *pvParameters);



#endif /* TASK_ACCELEROMETER_H_ */
