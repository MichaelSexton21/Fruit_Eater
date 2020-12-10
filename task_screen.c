/*
 * task_buzzer.c
 *
 * Author: Michael Sexton and Jack Bybel
 *
 */

#include <task_screen.h>
TaskHandle_t Task_Screen_Handle;

// state control variables to determine what state the game is in
bool START = true;
bool END = false;

// cursor for printing letters to the screen
int char_x;
int char_y;
volatile uint32_t TIMER; // elapsed time

/******************************************************************************
 * This function prints a word to the screen given the word, and length
 ******************************************************************************/
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

/******************************************************************************
 * Displays the start screen
 ******************************************************************************/
void Start_Screen(){

    char_x = 20;
    char_y = 40;
    //arrays defining the text to be displayed by creating lookup values
    uint16_t welcome[] = {'W'-'0','e'-'0','l'-'0','c'-'0','o'-'0','m'-'0','e'-'0'};//{40,54,61,52,64,62,54};
    uint16_t to[] = {'t'-'0','o'-'0'};
    uint16_t fruit[] = {'F'-'0','r'-'0','u'-'0','i'-'0','t'-'0'};
    uint16_t eater[] = {'E'-'0','a'-'0','t'-'0','e'-'0','r'-'0'};
    uint16_t press[] = {'P'-'0','r'-'0','e'-'0','s'-'0','s'-'0'};
    uint16_t s1[] = {'S'-'0','1'-'0'};
    uint16_t start[] = {'S'-'0','t'-'0','a'-'0','r'-'0','t'-'0'};

    //print each word to be displayed in the start screen
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

    while(!(P5->IN & BIT1) == 0){} //wait until S1 is pressed to start

    Draw_Black_Screen(); //make the screen blank to start

    vTaskDelay(100);

}

/******************************************************************************
 * Prints the numbers used in the end score
 ******************************************************************************/
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

/******************************************************************************
 * Displays the End screen
 ******************************************************************************/
void End_Screen(){
    //song to be played at the end
    uint8_t song = 1;
    //coordinates for where to print the words
    char_x = 20;
    char_y = 40;

    //once again arrays to define the words to be printed
    uint16_t congratulations[] = {'C'-'0','O'-'0','N'-'0','G'-'0','R'-'0','A'-'0','T'-'0','U'-'0','L'-'0','A'-'0','T'-'0','I'-'0','O'-'0','N'-'0','S'-'0'};
    uint16_t your[] = {'Y'-'0','o'-'0','u'-'0','r'-'0'};
    uint16_t score[] = {'S'-'0','c'-'0','o'-'0','r'-'0','e'-'0'};
    uint16_t is[] = {'i'-'0','s'-'0'};

    Draw_Black_Screen();

    //print message
    Print_Words(congratulations,15);
    char_x = 20; //changing where the words are to be printed so they don't overlap
    char_y = char_y+10;

    Print_Words(your,4);
    char_x = 20;
    char_y = char_y+10;

    Print_Words(score,5);
    char_x = char_x+10;

    Print_Words(is,2);
    char_x = 20;
    char_y = char_y+10;

    // convert the score to a string
    char STR_SCORE[5];
    sprintf(STR_SCORE, "%u", TOTAL_SCORE);

    // check if score is one digit or two
    int i;
    int x;
    if(STR_SCORE[1] == '\0'){
         x=2;
         i=1;
     }else{
         x=2;
     }

    // main logic for printing one or two digits
    // print numbers prints the bitmap equiavlent of the char
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
    //play the ending music
    xQueueSend(Queue_Music, &song, portMAX_DELAY);

    //wait until S1 is pressed
    while(!(P5->IN & BIT1) == 0){}

    //start timer
    Draw_Black_Screen();
    vTaskDelay(100);

}

//***************************************************************
// Displays the start and end screen
//***************************************************************
void Task_Screen(void *pvParameters)
{

    //check for the start of the game
    while(1){
        if(START){
            Start_Screen();//if so display the start screen
            START = false;
            vTaskPrioritySet(Task_Screen_Handle,1); // decrease the priority

        }else if(END){ // check for end of the game at end of task_packman.c

            vTaskPrioritySet(Task_Buzzer_Handle, 4); // increase the prority
            End_Screen(); //if so display end screen
            vTaskPrioritySet(Task_Buzzer_Handle, 1);
        }
        PACKMAN_MSG_t direction; //if no inputs keep pacman with a center command
        direction.cmd = PACKMAN_CMD_CENTER;
        direction.value = 0;
        xQueueSend(Queue_Packman, &direction, portMAX_DELAY);
    }
}
