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
     i2c_write_16(I2C_OPT3001_ADDRESS, I2C_OPT3001_CONFIG_REG, OPT3001_AUTOMATIC | OPT3001_CONTINUOUS);

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
  * Returns the current temperature in degrees C.
  ******************************************************************************/
 uint32_t OPT3001_get_lux(void)
 {
//     xSemaphoreTake(Sem_Console, portMAX_DELAY);
//     printf("OPT3001_get_lux\n\r");
//     xSemaphoreGive(Sem_Console);

     /* Specify slave address for OPT3001 */
     //i2c_set_slave_address(I2C_OPT3001_ADDRESS);

        uint16_t exponent = 0;
        uint16_t fractional_result = 0;
        uint32_t result = 0;
        int16_t raw;
        raw = i2c_read_16(I2C_OPT3001_ADDRESS, I2C_OPT3001_RESULT_REG);

        /*Convert to LUX*/
        //extract result & exponent data from raw readings
        result = raw&0x0FFF;
        exponent = (raw>>12)&0x000F;
        fractional_result = (raw&0x0FFF);

        result = 0.01*(2<<exponent)*fractional_result;


//        xSemaphoreTake(Sem_Console, portMAX_DELAY);
//         printf("end of OPT3001_get_lux\n\r");
//         xSemaphoreGive(Sem_Console);

        return result;
 }


void print_device_id(){
    //i2c_read_16(I2C_OPT3001_ADDRESS, I2C_OPT3001_DEVICE_ID);

    xSemaphoreTake(Sem_Console, portMAX_DELAY);
    printf("\n\r");

    char device_id[20];
    sprintf(device_id, "%04x", i2c_read_16(I2C_OPT3001_ADDRESS, I2C_OPT3001_DEVICE_ID));

    printf("DEVICE_ID: \n\r");
    printf(device_id);
    printf("\n\r");

     xSemaphoreGive(Sem_Console);
}

void print_manufacturer_id(){
    xSemaphoreTake(Sem_Console, portMAX_DELAY);

    printf("\n\r");
    char manufacturer_id[20];
    sprintf(manufacturer_id, "%04x",i2c_read_16(I2C_OPT3001_ADDRESS, I2C_OPT3001_MANUFACTURER_ID));

    printf("MANUFACTURER_ID: \n\r");
    printf(manufacturer_id);
    printf("\n\r");
    printf("\n\r");

    xSemaphoreGive(Sem_Console);
}
/******************************************************************************
* Bottom Half Task.  Examines the ADC data from the joy stick on the MKII
******************************************************************************/
void Task_Light_Sensor(void *pvParameters)
{
    uint32_t lux;

    while(1)
        {
            vTaskDelay(pdMS_TO_TICKS(250));

            xSemaphoreTake(Sem_Console, portMAX_DELAY);
            printf("Task_Light_Sensor\n\r");
            xSemaphoreGive(Sem_Console);
//            print_device_id();
//            print_manufacturer_id();
            lux = OPT3001_get_lux();

//            char string[20];
//            sprintf(string, "%zu", lux); // "%f" for float //"%zu" for int
//
//            xSemaphoreTake(Sem_Console, portMAX_DELAY);
//            printf(string);
//            xSemaphoreGive(Sem_Console);





        }
}

