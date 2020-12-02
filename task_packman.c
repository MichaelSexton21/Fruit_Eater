/*
 * task_space_ship.c
 *
 *  Created on: Nov 25, 2020
 *  Authors: Michael Sexton and John Bybel
 *
 */

#include <main.h>

#define SHIP_QUEUE_LEN  2

TaskHandle_t Task_Packman_Handle;
QueueHandle_t Queue_Packman;

/******************************************************************************
 * This function will initialize Queue_Packman and initialize the LCD
 ******************************************************************************/
void Task_Packman_Init(void)
{
    // Initiate Queue_Packman
    Queue_Packman = xQueueCreate(SHIP_QUEUE_LEN,sizeof(SHIP_MSG_t));
    // Initialize the Port
    HAL_LCD_PortInit();
    // Initialize the SPI interface
    HAL_LCD_SpiInit();
    // Initialize the LCD
    Crystalfontz128x128_Init();

}


/******************************************************************************
 * This task manages the movement of the space ship. The joystick task or the
 * console task can send messages to SHIP_QUEUE_LEN
 ******************************************************************************/
void Task_Packman(void *pvParameters)
{
    uint8_t x = 64;
    uint8_t y = 64;
    uint8_t dir = 0; // Which way to point packman
    SHIP_MSG_t direction;
    int speed = 25; // Delay between movements
    int pixelsToMove; // Number of pixels the spaceship needs to be moved

    // Draw the initial starting image of the spaceship.
    lcd_draw_image(
            x,
            y,
            packman_rightWidthPixels,
            packman_rightHeightPixels,
            packman_rightBitmaps,
            Packman_Color,
            LCD_COLOR_BLACK
    );

    // So the task never exits
    while(1)
    {
        // Wait for data to be in the queue
        xQueueReceive(Queue_Packman, &direction, portMAX_DELAY);
        printf("Task_Packman\n\r");

        // if the direction is speed, update the speed and don't move
        if(direction.cmd == SHIP_CMD_SPEED){
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
        if(direction.cmd == SHIP_CMD_LEFT  && x > 27){
            dir = 0;
            x--;
        }else if (direction.cmd == SHIP_CMD_RIGHT && x < 105){
            dir = 1;
            x++;
        }else if (direction.cmd == SHIP_CMD_UP && y > 20){
            dir = 2;
            y--;
        }else if (direction.cmd == SHIP_CMD_DOWN && y < 114){
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
            lcd_draw_image(
                        x,
                        y,
                        packman_leftWidthPixels,
                        packman_leftHeightPixels,
                        packman_leftBitmaps,
                        Packman_Color,
                        LCD_COLOR_BLACK
                );
        }else if(dir==1){
            lcd_draw_image(
                        x,
                        y,
                        packman_rightWidthPixels,
                        packman_rightHeightPixels,
                        packman_rightBitmaps,
                        Packman_Color,
                        LCD_COLOR_BLACK
                );
        }else if(dir==2){
            lcd_draw_image(
                        x,
                        y,
                        packman_upWidthPixels,
                        packman_upHeightPixels,
                        packman_upBitmaps,
                        Packman_Color,
                        LCD_COLOR_BLACK
                );
        }else if(dir==3){
            lcd_draw_image(
                        x,
                        y,
                        packman_downWidthPixels,
                        packman_downHeightPixels,
                        packman_downBitmaps,
                        Packman_Color,
                        LCD_COLOR_BLACK
                );
        }
        dir = -1;
        // delay for speed ms
        vTaskDelay(pdMS_TO_TICKS(speed));
        }

    }
}


