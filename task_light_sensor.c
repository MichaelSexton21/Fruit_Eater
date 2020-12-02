/*
 * task_accelerometer.c
 *
 *  Created on: Nov 25, 2020
 *  Authors: Michael Sexton and John Bybel
 *
 */

#include <main.h>
#include "task_light_sensor.h"


 TaskHandle_t Task_Light_Sensor_Handle;
 TaskHandle_t Task_Light_Sensor_Timer_Handle;


 /******************************************************************************
  * Initialize the tmp006 temperature sensor on the MKII.  This function assumes
  * that the I2C interface has already been configured to operate at 100KHz.
  ******************************************************************************/
 void OPT3001_init(void)
 {
     int i;

     // Reset the device using the CONFIG register
     i2c_write_16(I2C_OPT3001_ADDRESS, I2C_OPT3001_CONFIG_REG, OPT3001_RST);

     // delay
     for(i = 0; i < 50000; i++){};

     // Program the CONFIG register to POWER_UP and begin CR_2 mode
     i2c_write_16(I2C_OPT3001_ADDRESS, I2C_OPT3001_CONFIG_REG, OPT3001_POWER_UP | OPT3001_CR_2);
     //i2c_write_16(I2C_TEMP_ADDR, I2C_TEMP_CONFIG, TMP006_CR_2);
 }

/******************************************************************************
* This function will run the same configuration code that you would have
* written for HW02.
******************************************************************************/
 void Task_Light_Sensor_Init(void)
 {
     i2c_init();
     OPT3001_init();
 }

 /******************************************************************************
 * Used to start an ADC14 Conversion
 ******************************************************************************/
 void Task_Light_Sensor_Timer(void *pvParameters)
 {
     BaseType_t xHigherPriorityTaskWoken = pdFALSE;
     while(1)
     {
         printf("Task_Light_Sensor_Timer\n\r");
         vTaskNotifyGiveFromISR(Task_Light_Sensor_Handle,&xHigherPriorityTaskWoken);
             portYIELD_FROM_ISR( xHigherPriorityTaskWoken );

         // Delay 5ms
         vTaskDelay(pdMS_TO_TICKS(5));


     }
 }



 /******************************************************************************
  * Returns the current temperature in degrees C.
  ******************************************************************************/
 float OPT3001_get_lux(void)
 {
     /* Specify slave address for OPT3001 */
     i2c_set_slave_address(I2C_OPT3001_ADDRESS);

        uint16_t exponent = 0;
        uint32_t result = 0;
        int16_t raw;
        raw = i2c_read_16(I2C_OPT3001_RESULT_REG, I2C_OPT3001_CONFIG_REG);
        /*Convert to LUX*/
        //extract result & exponent data from raw readings
        result = raw&0x0FFF;
        exponent = (raw>>12)&0x000F;
        //convert raw readings to LUX
        switch(exponent){
        case 0: //*0.015625
            result = result>>6;
            break;
        case 1: //*0.03125
            result = result>>5;
            break;
        case 2: //*0.0625
            result = result>>4;
            break;
        case 3: //*0.125
            result = result>>3;
            break;
        case 4: //*0.25
            result = result>>2;
            break;
        case 5: //*0.5
            result = result>>1;
            break;
        case 6:
            result = result;
            break;
        case 7: //*2
            result = result<<1;
            break;
        case 8: //*4
            result = result<<2;
            break;
        case 9: //*8
            result = result<<3;
            break;
        case 10: //*16
            result = result<<4;
            break;
        case 11: //*32
            result = result<<5;
            break;
        }
        return result;
 }



/******************************************************************************
* Bottom Half Task.  Examines the ADC data from the joy stick on the MKII
******************************************************************************/
void Task_Light_Sensor(void *pvParameters)
{
    float lux;

    while(1)
        {
        printf("Task_Light_Sensor\n\r");
            // Wait until we get a task notification from the ADC14 ISR
            ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
            lux = OPT3001_get_lux();
            char string[20];
            sprintf(string, "%f", lux);
            printf(string);

//                xQueueSend(Queue_Packman, &direction, portMAX_DELAY);


        }
}

