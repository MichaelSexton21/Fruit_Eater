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
    SHIP_CMD_LEFT,
    SHIP_CMD_RIGHT,
    SHIP_CMD_UP,
    SHIP_CMD_DOWN,
    SHIP_CMD_CENTER,
    SHIP_CMD_SPEED
} SHIP_CMD_t;

typedef struct {
    SHIP_CMD_t cmd;
    uint8_t     value;
}SHIP_MSG_t;

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
