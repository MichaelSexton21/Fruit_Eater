/*
 * task_space_ship.h
 *
 *  Created on: Nov 25, 2020
 *  Authors: Michael Sexton and John Bybel
 *
 */

#ifndef TASK_PACKMAN_H_
#define TASK_PACKMAN_H_

#include <main.h>

typedef enum {
    PACKMAN_CMD_LEFT,
    PACKMAN_CMD_RIGHT,
    PACKMAN_CMD_UP,
    PACKMAN_CMD_DOWN,
    PACKMAN_CMD_CENTER,
    PACKMAN_CMD_SPEED
} SHIP_CMD_t;

typedef struct {
    SHIP_CMD_t cmd;
    uint8_t     value;
}PACKMAN_MSG_t;

extern TaskHandle_t Task_Packman_Handle;
extern QueueHandle_t Queue_Packman;

/******************************************************************************
 * This function will initialize Queue_Packman
 ******************************************************************************/
void Task_Packman_Init(void);

/******************************************************************************
 * This task manages the movement of the space ship. The joystick task or the
 * console task can send messages to the
 ******************************************************************************/
void Task_Packman(void *pvParameters);

void Draw_Packman(void);

#endif /* TASK_PACKMAN_H_ */
