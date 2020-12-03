/*
 * task_space_ship.c
 *
 *  Created on: Nov 25, 2020
 *  Authors: Michael Sexton and John Bybel
 *
 */

#include <main.h>

#define PACKMAN_QUEUE_LEN  2

TaskHandle_t Task_Packman_Handle;
QueueHandle_t Queue_Packman;
uint8_t x = 64;
uint8_t y = 64;
uint8_t* current_packman_Bitmap = packman_rightBitmaps;


/******************************************************************************
 * This function will initialize Queue_Packman and initialize the LCD
 ******************************************************************************/
void Task_Packman_Init(void)
{
    // Initiate Queue_Packman
    Queue_Packman = xQueueCreate(PACKMAN_QUEUE_LEN,sizeof(PACKMAN_MSG_t));
    // Initialize the Port
    HAL_LCD_PortInit();
    // Initialize the SPI interface
    HAL_LCD_SpiInit();
    // Initialize the LCD
    Crystalfontz128x128_Init();

}

void Draw_Packman(void){
    lcd_draw_image(
                x,
                y,
                packman_WidthPixels,
                packman_HeightPixels,
                current_packman_Bitmap,
                Packman_Color,
                LCD_COLOR_BLACK
        );
}
/******************************************************************************
 * This task manages the movement of the space ship. The joystick task or the
 * console task can send messages to SHIP_QUEUE_LEN
 ******************************************************************************/
void Task_Packman(void *pvParameters)
{

    uint8_t dir = 0; // Which way to point packman
    PACKMAN_MSG_t direction;
    int speed = 25; // Delay between movements
    int pixelsToMove; // Number of pixels the spaceship needs to be moved

    // Draw the initial starting image of the spaceship.
    Draw_Packman();

    // So the task never exits
    while(1)
    {
        // Wait for data to be in the queue
        xQueueReceive(Queue_Packman, &direction, portMAX_DELAY);
        //printf("Task_Packman\n\r");

        // if the direction is speed, update the speed and don't move
        if(direction.cmd == PACKMAN_CMD_SPEED){
            speed=direction.value;
            pixelsToMove = 0;
        }else{
            // otherwise, update the amount of pixels to move
            pixelsToMove = direction.value;
        }

        // While there are still pixels to move, update the spaceship
        while(pixelsToMove > 0){
            pixelsToMove--; // decrement the loop control variable

        // Move the picture by one pixel with each loop and don't exceede the bounds of the screen
        if(direction.cmd == PACKMAN_CMD_LEFT  && x > 12){
            dir = 0;
            x--;
        }else if (direction.cmd == PACKMAN_CMD_RIGHT && x < 120){
            dir = 1;
            x++;
        }else if (direction.cmd == PACKMAN_CMD_UP && y > 15){
            dir = 2;
            y--;
        }else if (direction.cmd == PACKMAN_CMD_DOWN && y < 120){
            dir = 3;
            y++;
        }else{
            // If the ammount to move is greater than the screen, a lag is created while
            // waiting for the delay to finish but the picture no longer moves. Setting
            // the pixels to move to be 0 eliminates that delay once the picture hits the
            // edge of the screen
            pixelsToMove = 0;
            dir = 1;
        }
        // draw the space ship
        if(dir==0){
            current_packman_Bitmap = packman_leftBitmaps;
        }else if(dir==1){
            current_packman_Bitmap = packman_rightBitmaps;
        }else if(dir==2){
            current_packman_Bitmap = packman_upBitmaps;
        }else if(dir==3){
            current_packman_Bitmap = packman_downBitmaps;
        }
        dir = 4;
        Draw_Packman();
        // delay for speed ms
        vTaskDelay(pdMS_TO_TICKS(speed));
        }

    }
}


