/*
 * task_console.h
 *
 *  Created on: Nov 25, 2020
 *  Authors: Michael Sexton and Jack Bybel
 *
 */

#ifndef TASK_CONSOLE_H_
#define TASK_CONSOLE_H_

#include <main.h>

extern QueueHandle_t Queue_Console;
extern SemaphoreHandle_t Sem_Console;

/******************************************************************************
 * This function configures the eUSCI_A0 to be a UART that communicates at
 * 115200 8N1.
 ******************************************************************************/
void Task_Console_Init(void);


#endif /* TASK_CONSOLE_H_ */
