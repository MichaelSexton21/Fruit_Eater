/*
 * task_buzzer.c
 *
 * Author: Michael Sexton
 *
 */

#include <task_screen.h>
TaskHandle_t Task_Screen_Handle;
bool start = true;
bool end = false;


void S1_Init(void){
    P5->DIR &= !BIT0;
}

void Task_Screen_Init(void)
{

    S1_Init();

}


void Start_Screen(){

    uint16_t welcome[] = {'W'-'0','e'-'0','l'-'0','c'-'0','o'-'0','m'-'0','e'-'0'};//{40,54,61,52,64,62,54};
    uint16_t to[] = {'t'-'0','o'-'0'};
    uint16_t fruit[] = {'F'-'0','r'-'0','u'-'0','i'-'0','t'-'0'};
    uint16_t eater[] = {'E'-'0','a'-'0','t'-'0','e'-'0','r'-'0'};
    Draw_Black_Screen();
    int i=0;
    int x=20;
    int y=40;
    for(i=0;i<7;i++){
        lcd_draw_image(
            x,
            y,
            microsoftSansSerif_8ptDescriptors[welcome[i]].widthBits,
            //microsoftSansSerif_8ptFontInfo.height*8,
            9,
            &microsoftSansSerif_8ptBitmaps[microsoftSansSerif_8ptDescriptors[welcome[i]].offset],
            LCD_COLOR_RED,
            LCD_COLOR_BLACK
        );
        x=x+7;
    }
    x = x+10;

    for(i=0;i<2;i++){
            lcd_draw_image(
                x,
                y,
                microsoftSansSerif_8ptDescriptors[to[i]].widthBits,
                //microsoftSansSerif_8ptFontInfo.height*8,
                9,
                &microsoftSansSerif_8ptBitmaps[microsoftSansSerif_8ptDescriptors[to[i]].offset],
                LCD_COLOR_RED,
                LCD_COLOR_BLACK
            );
            x=x+7;
        }
    x = 20;
    y = y+10;

    for(i=0;i<5;i++){
            lcd_draw_image(
                x,
                y,
                microsoftSansSerif_8ptDescriptors[fruit[i]].widthBits,
                //microsoftSansSerif_8ptFontInfo.height*8,
                9,
                &microsoftSansSerif_8ptBitmaps[microsoftSansSerif_8ptDescriptors[fruit[i]].offset],
                LCD_COLOR_RED,
                LCD_COLOR_BLACK
            );
            x=x+7;
        }
    x = x+10;

    for(i=0;i<5;i++){
            lcd_draw_image(
                x,
                y,
                microsoftSansSerif_8ptDescriptors[eater[i]].widthBits,
                //microsoftSansSerif_8ptFontInfo.height*8,
                9,
                &microsoftSansSerif_8ptBitmaps[microsoftSansSerif_8ptDescriptors[eater[i]].offset],
                LCD_COLOR_RED,
                LCD_COLOR_BLACK
            );
            x=x+7;
        }
    x = x+10;


    while(!(P5->IN & BIT1) == 0){}
    Draw_Black_Screen();
    vTaskDelay(100);

}

//***************************************************************
// Plays the song (loop through, playing each note)
// and then returns
//***************************************************************
void Task_Screen(void *pvParameters)
{

    while(1){
        if(start){
            Start_Screen();
            printf("finished");
            start = false;
            if(!start){
                printf("false");
            }

            vTaskPrioritySet( Task_Screen_Handle,3 );
        }else if(end){

        }
        PACKMAN_MSG_t direction;
        direction.cmd = PACKMAN_CMD_CENTER;
        direction.value = 0;
        xQueueSend(Queue_Packman, &direction, portMAX_DELAY);
    }


}
