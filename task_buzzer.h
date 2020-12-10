/*
 * task_buzzer.h
 *
 *      Author: Michael Sexton and Jack Bybel
 */

#ifndef TASK_BUZZER_H_
#define TASK_BUZZER_H_

#include <stdint.h>
#include <stdbool.h>
#include "msp.h"
#include <main.h>

#define NOTE_A6S 12868 // 1864.66 Hz
#define NOTE_A6 13636 // 1760.00 Hz
#define NOTE_G6S 14447 // 1661.22 Hz
#define NOTE_G6 15306 // 1567.98 Hz
#define NOTE_F6S 16216 // 1479.98 Hz
#define NOTE_F6 17180 // 1396.91 Hz
#define NOTE_E6 18202 // 1318.51 Hz
#define NOTE_D6S 19284 // 1244.51 Hz
#define NOTE_D6 20431 // 1174.66 Hz
#define NOTE_C6S 21646 // 1108.73 Hz
#define NOTE_C6 22933 // 1046.50 Hz
#define NOTE_B5 24297 // 987.767 Hz
#define NOTE_A5S 25742 // 932.328 Hz
#define NOTE_A5 27272 // 880.000 Hz
#define NOTE_G5S 28894 // 830.609 Hz
#define NOTE_G5 30612 // 783.991 Hz
#define NOTE_F5S 32432 // 739.989 Hz
#define NOTE_F5 34361 // 698.456 Hz
#define NOTE_E5 36404 // 659.255 Hz
#define NOTE_D5S 38569 // 622.254 Hz
#define NOTE_D5 40862 // 587.330 Hz
#define NOTE_C5S 43292 // 554.365 Hz
#define NOTE_C5 45867 // 523.251 Hz
#define NOTE_B4 48594 // 493.883 Hz
#define NOTE_A4S 51484 // 466.164 Hz
#define NOTE_A4 54545 // 440.000 Hz
#define NOTE_G4S 57788 // 415.305 Hz
#define NOTE_G4 61225 // 391.995 Hz
#define NOTE_F4S 64865 // 369.994 Hz
#define NOTE_F4 65531

//Cannot handle any notes greater than 65531

#define MEASURE_DURATION 12000000    // 500 milliseconds
#define MEASURE_RATIO           4    // 2/4 time
#define DELAY_AMOUNT       240000    // 10  milliseconds
#define SONG_NUM_NOTES 31

extern TaskHandle_t Task_Buzzer_Handle;
extern QueueHandle_t Queue_Music;
//extern uint8_t MUSIC_QUEUE_LEN = 2;

typedef enum measure_time_t {
    ONE_QUARTER,
    ONE_HALF,
    ONE_EIGTH,
    THREE_EIGTH
} measure_time_t;

typedef struct{
    uint32_t period;
    measure_time_t time;
    bool delay;
}Note_t;

//***************************************************************
//***************************************************************
void Task_Buzzer_Init(void);

//***************************************************************
//***************************************************************
void Task_Buzzer(void *pvParameters);

#endif /* TASK_BUZZER_H_ */
