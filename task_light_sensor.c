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
 uint16_t Packman_Color = LCD_COLOR_WHITE;


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
    uint32_t previous_lux;
    uint16_t color = 0xFFFA;

    while(1)
        {
            vTaskDelay(pdMS_TO_TICKS(250));

            xSemaphoreTake(Sem_Console, portMAX_DELAY);
            printf("Task_Light_Sensor\n\r");
            xSemaphoreGive(Sem_Console);
//            print_device_id();
//            print_manufacturer_id();
            lux = OPT3001_get_lux();

//            char curr_lux[20];
//            sprintf(curr_lux, "%zu", lux); // "%f" for float //"%zu" for int
//            char prev_lux[20];
//            sprintf(prev_lux, "%zu", lux);
//            xSemaphoreTake(Sem_Console, portMAX_DELAY);
//            printf("Current Lux: \n\r");
//            printf(curr_lux);
//            printf("\n\r");
//            printf("Previous Lux: \n\r");
//            printf(prev_lux);
//            printf("\n\r");
//            xSemaphoreGive(Sem_Console);

//            if(lux < previous_lux && color < 0xDDDD){
//                Packman_Color = color+0x0222;
//            }else if(lux > previous_lux && color >0x0222){
//                Packman_Color = color-0x0222;
//            }else{
//                Packman_Color = color;
//            }

            if(lux<100){
                Packman_Color = LCD_COLOR_WHITE;
            }else if(lux>100 && lux <200){
                Packman_Color = LCD_COLOR_MAGENTA;
            }else if(lux>200 && lux <300){
                Packman_Color = LCD_COLOR_BLUE2;
            }else if(lux>300 && lux <400){
                Packman_Color = LCD_COLOR_BLUE2;
            }else if(lux>400 && lux <500){
                Packman_Color = LCD_COLOR_GREEN2;
            }else if(lux>500 && lux <800){
                Packman_Color = LCD_COLOR_GREEN;
            }else if(lux>800 && lux <1000){
                Packman_Color = LCD_COLOR_RED;
            }else if(lux>1000 && lux <1300){
                Packman_Color = LCD_COLOR_ORANGE ;
            }else if(lux>1300 && lux <1700){
                Packman_Color = LCD_COLOR_CYAN;
            }else if(lux>1700){
                Packman_Color = LCD_COLOR_YELLOW;
            }

            Draw_Fruit();
            Draw_Packman();
            previous_lux = lux;

        }
}

