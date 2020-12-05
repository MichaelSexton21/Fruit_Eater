/*
 * task_space_ship.c
 *
 *  Created on: Nov 25, 2020
 *  Authors: Michael Sexton and John Bybel
 *
 */

#include <main.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <grlib.h>
Graphics_Context g_sContext;

#define PACKMAN_QUEUE_LEN  2

TaskHandle_t Task_Packman_Handle;
QueueHandle_t Queue_Packman;
uint8_t x = 64;
uint8_t y = 64;
volatile uint8_t fruit_x;
volatile uint8_t fruit_y;
uint8_t* current_packman_Bitmap = packman_rightBitmaps;
uint8_t* current_fruit_Bitmap = orangeBitmaps;
uint8_t current_fruit = 0;
uint8_t score = 0;


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



void Update_Random_Fruit_Coordinates(){

   // Intializes random number generator
   //srand((unsigned) time(&t));
    uint32_t distance = sqrt((pow(fruit_x-x,2)+pow(fruit_y-y,2)));

    //while(distance<25){

       fruit_x = (rand() % (117 - 15 + 1)) + 15;  //rand() % 133;
       fruit_y = (rand() % (117 - 15 + 1)) + 15;
       distance = sqrt((pow(fruit_x-x,2)+pow(fruit_y-y,2)));
    //}
}

void Draw_Fruit(void){
    if(current_fruit == 0){
        current_fruit_Bitmap = orangeBitmaps;
    }else if(current_fruit == 1){
        current_fruit_Bitmap = bannanaBitmaps;
    }else if(current_fruit ==2){
        current_fruit_Bitmap = appleBitmaps;
        current_fruit=0;
    }
    lcd_draw_image(
                fruit_x,
                fruit_y,
                fruitWidthPixels,
                fruitHeightPixels,
                current_fruit_Bitmap,
                Packman_Color,
                LCD_COLOR_BLACK
        );
}

void Draw_Black_Screen(){
    lcd_draw_image(
                    fruit_x,
                    fruit_y,
                    blankWidthPixels,
                    blankHeightPixels,
                    blankScreenBitmaps,
                    LCD_COLOR_BLACK,
                    LCD_COLOR_BLACK
            );
}

bool Collision_Check(){

    char X[20];
    uint32_t distance = sqrt((pow(fruit_x-x,2)+pow(fruit_y-y,2)));

    if(distance<17)
        return true;
    else
        return false;

    sprintf(X, "%zu", distance);
    printf("\n\r");
    printf(X);

//    if(fruit_x-8 < x && fruit_x+8 > x)
//        return true;
//    else if(fruit_y-8 < x && fruit_y > y)
//        return true;
//    else
}

/******************************************************************************
 * This task manages the movement of the space ship. The joystick task or the
 * console task can send messages to SHIP_QUEUE_LEN
 ******************************************************************************/
void Task_Packman(void *pvParameters)
{

    printf("Task_Packman");
    srand(time(0));
    uint8_t dir = 0; // Which way to point packman
    PACKMAN_MSG_t direction;
    int speed = 25; // Delay between movements
    int pixelsToMove; // Number of pixels packman needs to move
    uint8_t song= 0;

    // Draw the initial starting image of packman.
    Draw_Packman();
    Update_Random_Fruit_Coordinates();
    Draw_Fruit();
    current_fruit++;

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

        // Move the picture by one pixel with each loop and don't exceed the bounds of the screen
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
        // draw the packman
        if(dir==0){
            current_packman_Bitmap = packman_leftBitmaps;
        }else if(dir==1){
            current_packman_Bitmap = packman_rightBitmaps;
        }else if(dir==2){
            current_packman_Bitmap = packman_upBitmaps;
        }else if(dir==3){
            current_packman_Bitmap = packman_downBitmaps;
        }

        if(Collision_Check()){
            song = 0;
            xQueueSend(Queue_Music, &song, portMAX_DELAY);
            Draw_Black_Screen();
            score++;
            Update_Random_Fruit_Coordinates();
            Draw_Fruit();
            current_fruit++;
            printf("\n\r");
            printf("Score: \n\r");
            char X[20];
            sprintf(X, "%zu", score);
            printf(X);
        }
//        Graphics_drawStringCentered(&g_sContext,
//        (int8_t *)"Hello",
//        AUTO_STRING_LENGTH,
//        64,
//        30,
//        OPAQUE_TEXT);

        dir = 4;
        Draw_Packman();

        // delay for speed ms
        vTaskDelay(pdMS_TO_TICKS(speed));
        }

    }
}


