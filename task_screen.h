/*
 * task_buzzer.h
 *
 *      Author: Michael Sexton and Jack Bybel
 */

#ifndef TASK_SCREEN_H_
#define TASK_SCREEN_H_

#include <stdint.h>
#include <stdbool.h>
#include "msp.h"
#include <main.h>


extern TaskHandle_t Task_Screen_Handle;

//***************************************************************
//***************************************************************
void Task_Screen_Init(void);

//***************************************************************
//***************************************************************
void Task_Screen(void *pvParameters);

#endif /* TASK_SCREEN_H_ */
