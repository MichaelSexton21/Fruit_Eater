/*
 * task_buzzer.c
 *
 * Author: Michael Sexton
 *
 */

#include <task_screen.h>
TaskHandle_t Task_Screen_Handle;
bool START = true;
bool END = false;
int char_x;
int char_y;
volatile uint32_t TIMER;

void Task_Screen_Init(void)
{
    //P5->DIR &= !BIT0; // Initialize S1
    // ticks- desired period / core clock period
        // 20e-3/(1/3e6) = (3e6*20)/1000
        uint32_t ticks = ((SystemCoreClock * 32000)/1000) -1;

        // Stop the timer
        TIMER32_2->CONTROL = 0;
        // Set the load register
        TIMER32_2->LOAD = ticks;

        // Enable the Timer32 interrupt in NVIC
        __enable_irq();
        NVIC_EnableIRQ(T32_INT2_IRQn);
        NVIC_SetPriority(T32_INT2_IRQn, 3);

        TIMER32_2->CONTROL = TIMER32_CONTROL_ENABLE | // Turn timer on
                                     TIMER32_CONTROL_ONESHOT | // periodic mode
                                     TIMER32_CONTROL_SIZE | // 32 bit timer
                                     TIMER32_CONTROL_IE; // enable interrupts
printf("endINit");
}

void Print_Words(uint16_t word[], int length){
    int i=0;
    for(i=0;i<length;i++){
        lcd_draw_image(
            char_x,
            char_y,
            microsoftSansSerif_8ptDescriptors[word[i]].widthBits,
            9,
            &microsoftSansSerif_8ptBitmaps[microsoftSansSerif_8ptDescriptors[word[i]].offset],
            LCD_COLOR_RED,
            LCD_COLOR_BLACK
        );
        char_x=char_x+7;
        }
}

void Start_Screen(){

    char_x = 20;
    char_y = 40;

    uint16_t welcome[] = {'W'-'0','e'-'0','l'-'0','c'-'0','o'-'0','m'-'0','e'-'0'};//{40,54,61,52,64,62,54};
    uint16_t to[] = {'t'-'0','o'-'0'};
    uint16_t fruit[] = {'F'-'0','r'-'0','u'-'0','i'-'0','t'-'0'};
    uint16_t eater[] = {'E'-'0','a'-'0','t'-'0','e'-'0','r'-'0'};
    uint16_t press[] = {'P'-'0','r'-'0','e'-'0','s'-'0','s'-'0'};
    uint16_t s1[] = {'S'-'0','1'-'0'};
    uint16_t start[] = {'S'-'0','t'-'0','a'-'0','r'-'0','t'-'0'};
    uint16_t con[]={'C'-'0','O'-'0','N'-'0'};

    //Draw_Black_Screen();

    Print_Words(welcome,7);
    char_x = char_x+10;

    Print_Words(to,2);
    char_x = 20;
    char_y = char_y+10;

    Print_Words(fruit,5);
    char_x = char_x+10;

    Print_Words(eater,5);
    char_x = 20;
    char_y = char_y+10;

    Print_Words(press,5);
    char_x = char_x+10;

    Print_Words(s1,2);
    char_x = 20;
    char_y = char_y+10;

    Print_Words(start, 5);

printf("startScreen");
    while(!(P5->IN & BIT1) == 0){}

    Draw_Black_Screen();
    printf("here");
    vTaskDelay(100);

}

void Print_Numbers(char X){
        lcd_draw_image(
            char_x,
            char_y,
            microsoftSansSerif_8ptDescriptors[X-'0'].widthBits,
            9,
            &microsoftSansSerif_8ptBitmaps[microsoftSansSerif_8ptDescriptors[X-'0'].offset],
            LCD_COLOR_RED,
            LCD_COLOR_BLACK
        );
        char_x=char_x+7;

}

void End_Screen(){

    char_x = 20;
    char_y = 40;

    uint16_t congratulations[] = {'C'-'0','O'-'0','N'-'0','G'-'0','R'-'0','A'-'0','T'-'0','U'-'0','L'-'0','A'-'0','T'-'0','I'-'0','O'-'0','N'-'0','S'-'0'};
    uint16_t your[] = {'Y'-'0','o'-'0','u'-'0','r'-'0'};
    uint16_t score[] = {'S'-'0','c'-'0','o'-'0','r'-'0','e'-'0'};
    uint16_t is[] = {'i'-'0','s'-'0'};

    Draw_Black_Screen();

    Print_Words(congratulations,15);
    char_x = 20;
    char_y = char_y+10;

    Print_Words(your,4);
    char_x = 20;
    char_y = char_y+10;

    Print_Words(score,5);
    char_x = char_x+10;

    Print_Words(is,2);
    char_x = 20;
    char_y = char_y+10;

    xSemaphoreTake(Sem_Console, portMAX_DELAY);
    printf("SCORE:\n\r");

    char STR_SCORE[5];
    sprintf(STR_SCORE, "%u", TOTAL_SCORE);
    printf(STR_SCORE);
    printf("\n\r");

    int i;
    int x;
    if(STR_SCORE[1] == '\0'){
         x=2;
         i=1;
     }else{
         x=2;
     }

for(i=0;i<x;i++){
    if(STR_SCORE[i] == '0'){
        Print_Numbers('0');
    }else if(STR_SCORE[i] == '1'){
        Print_Numbers('1');
    }else if(STR_SCORE[i] == '2'){
        Print_Numbers('2');
    }else if(STR_SCORE[i] == '3'){
        Print_Numbers('3');
    }else if(STR_SCORE[i] == '4'){
        Print_Numbers('4');
    }else if(STR_SCORE[i] == '5'){
        Print_Numbers('5');
    }else if(STR_SCORE[i] == '6'){
        Print_Numbers('6');
    }else if(STR_SCORE[i] == '7'){
        Print_Numbers('7');
    }else if(STR_SCORE[i] == '8'){
        Print_Numbers('8');
    }else if(STR_SCORE[i] == '9'){
        Print_Numbers('9');
    }
}

    Print_Words((uint16_t*)(STR_SCORE[0]-'0'), 1);
    char_x = char_x+10;
    printf("first character printed");

    if(STR_SCORE[1] != '\0'){
        printf("not null");
        Print_Words((uint16_t*)(STR_SCORE[1]-'0'), 1);
    }


    xSemaphoreGive(Sem_Console);



    while(!(P5->IN & BIT1) == 0){}

    //start timer
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
        if(START){
            Start_Screen();
            START = false;

            vTaskPrioritySet( Task_Screen_Handle,3 );
        }else if(END){
            End_Screen();
        }
        PACKMAN_MSG_t direction;
        direction.cmd = PACKMAN_CMD_CENTER;
        direction.value = 0;
        xQueueSend(Queue_Packman, &direction, portMAX_DELAY);
    }


}

void T32_INT1_IRQHandler(void)
{

    printf("IRQ");
//    TIMER = TIMER32_1->VALUE;
    // Clear the timer interrupt
    TIMER32_1->INTCLR=BIT0;
    TIMER32_2->CONTROL = 0;

    END=true;
    vTaskDelay(pdMS_TO_TICKS(1000));
    vTaskPrioritySet( Task_Screen_Handle, 4);
}
