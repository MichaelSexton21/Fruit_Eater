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
#define I2C_OPT3001_MANUFACTURER_ID 0x7E
#define I2C_OPT3001_DEVICE_ID 0x7F
#define I2C_OPT3001_RESULT_REG 0x00
#define I2C_OPT3001_CONFIG_REG 0x01

/* CONFIGURATION REGISTER SETTINGS */
#define OPT3001_RST              0xC810
#define OPT3001_AUTOMATIC        0xC000
#define OPT3001_CONTINUOUS       0x0600

extern TaskHandle_t Task_Light_Sensor_Handle;

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
