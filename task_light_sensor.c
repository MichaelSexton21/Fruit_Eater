/*
 * task_light_sensor.c
 *
 *  Created on: Nov 25, 2020
 *  Authors: Michael Sexton and Jack Bybel
 *
 */

#include <main.h>
#include "task_light_sensor.h"


 TaskHandle_t Task_Light_Sensor_Bottom_Half_Handle;
 uint16_t Packman_Color = LCD_COLOR_WHITE; // initializes packman's color to white


 /******************************************************************************
  * Initialize the OPT3001 Light Sensor
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
* Initializes all Hardware needed for Task_Light_Sensor
******************************************************************************/
 void Task_Light_Sensor_Init(void)
 {
     i2c_init();
     OPT3001_init();
 }


 /******************************************************************************
  * Returns the current ambient light value in lux
  ******************************************************************************/
 uint32_t OPT3001_get_lux(void)
 {
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

        return result;
 }

 /******************************************************************************
  * Used for debugging prints the OPT3001 Device Id
  ******************************************************************************/
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

/******************************************************************************
 * Used for debugging prints the OPT3001 Manufacturer
 ******************************************************************************/
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
* Examines lux values from the Light Sensor
******************************************************************************/
void Task_Light_Sensor_Bottom_Half(void *pvParameters)
{
    uint32_t lux;
    PACKMAN_MSG_t direction;

    while(1)
        {
            vTaskDelay(pdMS_TO_TICKS(250));

//            print_device_id();
//            print_manufacturer_id();
            lux = OPT3001_get_lux();

            // change the color and speed of packman depending on the ambient light
            if(lux<100){
                Packman_Color = LCD_COLOR_WHITE;
                direction.value = 25;
            }else if(lux>100 && lux <200){
                Packman_Color = LCD_COLOR_MAGENTA;
                direction.value = 22.22;
            }else if(lux>200 && lux <300){
                Packman_Color = LCD_COLOR_BLUE2;
                direction.value = 19.44;
            }else if(lux>300 && lux <400){
                Packman_Color = LCD_COLOR_BLUE2;
                direction.value = 16.66;
            }else if(lux>400 && lux <500){
                Packman_Color = LCD_COLOR_GREEN2;
                direction.value = 13.88;
            }else if(lux>500 && lux <800){
                Packman_Color = LCD_COLOR_GREEN;
                direction.value = 11.11;
            }else if(lux>800 && lux <1000){
                Packman_Color = LCD_COLOR_RED;
                direction.value = 8.33;
            }else if(lux>1000 && lux <1300){
                Packman_Color = LCD_COLOR_ORANGE ;
                direction.value = 5.55;
            }else if(lux>1300 && lux <1700){
                Packman_Color = LCD_COLOR_CYAN;
                direction.value = 2.77;
            }else if(lux>1700){
                Packman_Color = LCD_COLOR_YELLOW;
                direction.value = 1;
            }

            // update the color of the fruit and packman
            Draw_Fruit();
            Draw_Packman();

            direction.cmd = PACKMAN_CMD_SPEED;
            xQueueSend(Queue_Packman, &direction, portMAX_DELAY);

        }
}

