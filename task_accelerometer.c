/*
 * task_accelerometer.c
 *
 *  Created on: Nov 25, 2020
 *  Authors: Michael Sexton and John Bybel
 *
 */

#include <main.h>


 TaskHandle_t Task_Accelerometer_Handle;
 TaskHandle_t Task_Accelerometer_Timer_Handle;

 volatile uint32_t JOYSTICK_X_DIR = 0;
 volatile uint32_t JOYSTICK_Y_DIR = 0;

/******************************************************************************
* This function will run the same configuration code that you would have
* written for HW02.
******************************************************************************/
 void Task_Accelerometer_Init(void)
 {
     // Configure the X direction as an analog input pin.
     P6->SEL0 |= BIT0;
     P6->SEL1 |= BIT0;

     // Configure the Y direction as an analog input pin.
     P4->SEL0 |= BIT4;
     P4->SEL1 |= BIT4;

     // Configure CTL0 to sample 16-times in pulsed sample mode.
     // NEW -- Indicate that this is a sequence of samples.
     ADC14->CTL0 = ADC14_CTL0_SHT0_2 | ADC14_CTL0_SHP | ADC14_CTL0_CONSEQ_1;

     // Configure CTL1 to return 12-bit values
     ADC14->CTL1 = ADC14_CTL1_RES_2;         // Use sampling timer, 12-bit conversion results

     // Associate the X direction analog signal with MEM[0]
     ADC14->MCTL[0] |= ADC14_MCTLN_INCH_15;

     // Associate the Y direction analog signal with MEM[1]
     // NEW -- Make sure to indicate this is the end of a sequence.
     ADC14->MCTL[1] |= ADC14_MCTLN_INCH_9 | ADC14_MCTLN_EOS;

     // Enable interrupts AFTER a value is written into MEM[1].
     ADC14->IER0 |= ADC14_IER0_IE1 ;

     // Enable ADC Interrupt
     NVIC_EnableIRQ(ADC14_IRQn);

     // Interrupt priorities must NOT be set to 0.  It is preferred if they are set to a value that is > than 1 too.
     NVIC_SetPriority(ADC14_IRQn,2);

     // Turn ADC ON
     ADC14->CTL0 |= ADC14_CTL0_ON;

 }

 /******************************************************************************
 * Used to start an ADC14 Conversion
 ******************************************************************************/
 void Task_Accelerometer_Timer(void *pvParameters)
 {
     while(1)
     {
         // Start the ADC conversion
         ADC14->CTL0 |= ADC14_CTL0_SC | ADC14_CTL0_ENC;

         // Delay 5ms
         vTaskDelay(pdMS_TO_TICKS(5));

     }
 }


/******************************************************************************
* Bottom Half Task.  Examines the ADC data from the joy stick on the MKII
******************************************************************************/
void Task_Accelerometer(void *pvParameters)
{
    SHIP_MSG_t direction;
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    while(1)
        {

            // Wait until we get a task notification from the ADC14 ISR
            ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

//            xSemaphoreTake(Sem_Console, portMAX_DELAY);
//            printf("Task_Accelerometer\n\r");
//            xSemaphoreGive(Sem_Console);

            /*
             * Set the dir variable to one of the following values based
             * on the values of JOYSTICK_X_DIR and JOYSTIC_Y_DIR
             */
            if(JOYSTICK_X_DIR < VOLT_0P85)
            {
               direction.cmd = SHIP_CMD_LEFT;
            }
            else if(JOYSTICK_X_DIR > VOLT_2P50)
            {
                direction.cmd = SHIP_CMD_RIGHT;
            }
            else if(JOYSTICK_Y_DIR < VOLT_0P85)
            {
                direction.cmd = SHIP_CMD_DOWN;
            }
            else if(JOYSTICK_Y_DIR > VOLT_2P50)
            {
                direction.cmd = SHIP_CMD_UP;
            }else{
                direction.cmd = SHIP_CMD_CENTER;
            }

            // set the value of the direction
            direction.value = 1;

            // Send dir to Queue_Console if the joystick is not at the center
            // as to not fill the queue with center commands
            if(direction.cmd != SHIP_CMD_CENTER){
                xQueueSend(Queue_Packman, &direction, portMAX_DELAY);
            }

        }
}


/******************************************************************************
* Top Half of ADC14 Handler.
******************************************************************************/
void ADC14_IRQHandler(void)
{

    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    JOYSTICK_X_DIR = ADC14->MEM[0]; // Read the value and clear the interrupt
    JOYSTICK_Y_DIR = ADC14->MEM[1]; // Read the value and clear the interrupt


    /*
     * Send a task notification to Task_Joystick_Bottom_Half
     */
    vTaskNotifyGiveFromISR(Task_Accelerometer_Handle,&xHigherPriorityTaskWoken);
    portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
}



