/*
 * task_console.c
 *
 *  Created on: Nov 25, 2020
 *  Authors: Michael Sexton and John Bybel
 *
 */
#include <main.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

QueueHandle_t Queue_Console;
TaskHandle_t Task_Console_Handle;
SemaphoreHandle_t Sem_Console;

#define RX_ARRAY_SIZE 10

// Global variables used to store incoming data from RXBUF.
volatile char RX_ARRAY[RX_ARRAY_SIZE];
volatile uint16_t RX_INDEX=0;


/******************************************************************************
 * This function configures the eUSCI_A0 to be a UART that communicates at
 * 115200 8N1.
 *
 * The configuration should be identical to what you have done
 * in a previous ICE-08 EXCEPT that you will need to set the priority of the
 * eUSCI to be a value that is equal to 2
 ******************************************************************************/
static void console_hw_init(void)
{
    // Configure the IO pins used for the UART
    // set 2-UART pin as secondary function
    P1->SEL0 |= BIT2 | BIT3;
    P1->SEL1 &= ~(BIT2 | BIT3);

    EUSCI_A0->CTLW0 |= EUSCI_A_CTLW0_SWRST; // Put eUSCI in reset
    EUSCI_A0->CTLW0 = EUSCI_A_CTLW0_SWRST | // Remain eUSCI in reset
            EUSCI_B_CTLW0_SSEL__SMCLK; // Configure eUSCI clock source

    // Baurd Rate calculation
    // 24000000/(16*115200) = 13.020833333
    // Fractional portion = 0.20833333
    // UCBRFx = int ( (13.020833333-13)*16) = 0
    EUSCI_A0->BRW = 13; // 24000000/16/115200

    // Set the fractional portion of the baud rate and turn
    // on oversampling
    EUSCI_A0->MCTLW = (0 << EUSCI_A_MCTLW_BRF_OFS) | EUSCI_A_MCTLW_OS16;

    // Enable eUSCI in UART mode
    EUSCI_A0->CTLW0 &= ~EUSCI_A_CTLW0_SWRST;

    // Clear any outstanding interrupts.
    EUSCI_A0->IFG &= ~(EUSCI_A_IFG_RXIFG | EUSCI_A_IFG_TXIFG);

    // Enable Rx Interrupt
    EUSCI_A0->IE |= EUSCI_A_IE_RXIE;

    // Enable EUSCIA0 Interrupt
    NVIC_EnableIRQ(EUSCIA0_IRQn);
    NVIC_SetPriority(EUSCIA0_IRQn, 2);

    // Prime the pump -- ADD CODE
    EUSCI_A0->TXBUF = 0;
}

/******************************************************************************
 * This function initializes the eUSCI_A0 hardware by calling console_hw_init().
 * It will also initialize Sem_Console.
 *
 * NOTE:  This function must be run prior to the FreeRTOS scheduler being
 * started.
 ******************************************************************************/
void Task_Console_Init(void)
{
    // Initialize the array used to hold UART data
    memset(RX_ARRAY,0,RX_ARRAY_SIZE);

    // Initialize UART
    console_hw_init();

    // Initialize the binary semaphore used to provide mutual exclusion to
    // the UART.
    Sem_Console = xSemaphoreCreateBinary();
    xSemaphoreGive(Sem_Console);

}

/*****************************************************
 * Needed to get printf to work using polling when
 * transmitting characters.
 *****************************************************/
int fputc(int c, FILE* stream)
{
    // while UART is busy, wait
    while(EUSCI_A0->STATW & EUSCI_A_STATW_BUSY){};

    //transmit the character
    EUSCI_A0->TXBUF = c;

    return 0;
}

//****************************************************************************
// UART interrupt service routine
// ****************************************************************************/
void EUSCIA0_IRQHandler(void)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    // Check for Rx interrupts
    if (EUSCI_A0->IFG & EUSCI_A_IFG_RXIFG)
    {
        // put the rx character into the buffer
        RX_ARRAY[RX_INDEX] = EUSCI_A0->RXBUF;

        // echo the character to the console
        EUSCI_A0->TXBUF = RX_ARRAY[RX_INDEX];

        // if enter is pressed
        if(RX_ARRAY[RX_INDEX] == '\n' || RX_ARRAY[RX_INDEX] == '\r'){

            // add the null terminator to the string
            RX_ARRAY[RX_INDEX] = '\0';
            // print an new line to the screen
            printf("\r\n");
            // Notify the console
            vTaskNotifyGiveFromISR(Task_Console_Handle, &xHigherPriorityTaskWoken);
            portYIELD_FROM_ISR( xHigherPriorityTaskWoken );

        }
        //increase the string index counter
        RX_INDEX++;

    }
}

/******************************************************************************
* Task used to parse the commands received by the UART
*
* Command  |    Description
*
* L 10          Move Left by 10 pixels
* R 5           Move Right by 5 pixels
* U 20          Move Up by 20 pixels
* D 4           Move Down by 4 pixels
* S 1           Set Ship Speed to 1mS/Pixel
******************************************************************************/
void Task_Console_Bottom_Half(void *pvParameters)
{
    while(1){

        PACKMAN_MSG_t direction;
        uint8_t value;

        // wait task to be called
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        // parse the recieved string and extract the number as a string
        char *dir =  strtok(RX_ARRAY, " "); // can ignore, must move the parse to the next string
        char *speed_string = strtok(NULL, " ");

        // convert the value to an integer
        value = atoi(speed_string);

        //Depending on which command was send, send it to the queue
        if(RX_ARRAY[0] == 'L'){
           direction.cmd = PACKMAN_CMD_LEFT;
        }else if(RX_ARRAY[0] == 'R'){
           direction.cmd = PACKMAN_CMD_RIGHT;
        }else if(RX_ARRAY[0] == 'U'){
            direction.cmd = PACKMAN_CMD_UP;
        }else if(RX_ARRAY[0] == 'D'){
            direction.cmd = PACKMAN_CMD_DOWN;
        }else if(RX_ARRAY[0] == 'S'){
            direction.cmd = PACKMAN_CMD_SPEED;
        }
        // set the value of the direction
        direction.value = value;

        // send it to the queue
        xQueueSend(Queue_Packman, &direction, portMAX_DELAY);
        // reset the index of the string array
        RX_INDEX = 0;
        // clear the array
        memset((void *)RX_ARRAY, 0, RX_ARRAY_SIZE);

    }
}


