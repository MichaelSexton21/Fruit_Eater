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

//*****************************************************************************
// You will need to determine the number of SMCLKs it will
// take for the following notes and their associated frequencies.
//
// Assume that your MCU is running at 24MHz.
//*****************************************************************************
//#define NOTE_A5        27272 // 880 Hz
//#define NOTE_A5S       25750 // 932 Hz
//#define NOTE_B5        24290 // 988 Hz
//#define NOTE_C6        22944 // 1046 Hz
//#define NOTE_C6S       21640 // 1109 Hz
//#define NOTE_D6        20425 // 1175 Hz
//#define NOTE_D6S       19276 // 1245 Hz
//#define NOTE_E6        18195 // 1319 Hz
//#define NOTE_F6        17179 // 1397 Hz
//#define NOTE_F6S       16215 // 1480 Hz
//#define NOTE_G6        15305 // 1568 Hz
//#define NOTE_G6S       14448 // 1661 Hz
//#define NOTE_A6        13635 // 1760 Hz
//#define NOTE_A6S       12868 // 1865 Hz
//#define NOTE_B6        12145 // 1976 Hz
//#define NOTE_C7        11466 // 2093 Hz
//#define NOTE_C7S       10824 // 2217 Hz
//#define NOTE_D7        10216 // 2349 Hz
//#define NOTE_D7S       9641 // 2489 Hz
//#define NOTE_E7        9100 // 2637 Hz
//#define NOTE_F7        8589 // 2794 Hz
//#define NOTE_F7S       8107 // 2960 Hz
//#define NOTE_G7        7652 // 3136 Hz
//#define NOTE_G7S       7224 // 3322 Hz

#define NOTE_C8 5733 // 4186.01 Hz
#define NOTE_B7 6074 // 3951.07 Hz
#define NOTE_A7S 6435 // 3729.31 Hz
#define NOTE_A7 6818 // 3520 Hz
#define NOTE_G7S 7223 // 3322.44 Hz
#define NOTE_G7 7653 // 3135.96 Hz
#define NOTE_F7S 8108 // 2959.96 Hz
#define NOTE_F7 8590 // 2793.83 Hz
#define NOTE_E7 9101 // 2637.02 Hz
#define NOTE_D7S 9642 // 2489.02 Hz
#define NOTE_D7 10215 // 2349.32 Hz
#define NOTE_C7S 10823 // 2217.46 Hz
#define NOTE_C7 11466 // 2093.00 Hz
#define NOTE_B6 12148 // 1975.53 Hz
#define NOTE_A6S 12870 // 1864.66 Hz
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
#define NOTE_F4 68723 // 349.228 Hz
#define NOTE_E4 72809 // 329.628 Hz
#define NOTE_D4S 77138 // 311.127 Hz
#define NOTE_D4 81725 // 293.665 Hz
#define NOTE_C4S 86585 // 277.183 Hz
#define NOTE_C4 91734 // 261.626 Hz
#define NOTE_B3 97188 // 246.942 Hz
#define NOTE_A3S 102968 // 233.082 Hz
#define NOTE_A3 109090 // 220.000 Hz
#define NOTE_G3S 115577 // 207.652 Hz
#define NOTE_G3 122450 // 195.998 Hz
#define NOTE_F3S 129731 // 184.997 Hz
#define NOTE_F3 137446 // 174.614 Hz
#define NOTE_E3 145618 // 164.814 Hz
#define NOTE_D3S 154278 // 155.563 Hz
#define NOTE_D3 163452 // 146.832 Hz
#define NOTE_C3S 173171 // 138.591 Hz
#define NOTE_C3 183468 // 130.813 Hz
#define NOTE_B2 194377 // 123.471 Hz
#define NOTE_A2S 205936 // 116.541 Hz
#define NOTE_A2 218181 // 110.000 Hz
#define NOTE_G2S 231155 // 103.826 Hz
#define NOTE_G2 244900 // 97.9989 Hz
#define NOTE_F2S 259463 // 92.4986 Hz
#define NOTE_F2 274891 // 87.3071 Hz
#define NOTE_E2 291237 // 82.4069 Hz
#define NOTE_D2S 308555 // 77.7817 Hz
#define NOTE_D2 326903 // 73.4162 Hz
#define NOTE_C2S 346341 // 69.2957 Hz
#define NOTE_C2 366936 // 65.4064 Hz
#define NOTE_B1 388755 // 61.7354 Hz
#define NOTE_A1S 411872 // 58.2705 Hz
#define NOTE_A1 436363 // 55.0000 Hz
#define NOTE_G1S 462311 // 51.9130 Hz
#define NOTE_G1 489800 // 48.9995 Hz
#define NOTE_F1S 518926 // 46.2493 Hz
#define NOTE_F1 549782 // 43.6536 Hz
#define NOTE_E1 582474 // 41.2035 Hz
#define NOTE_D1S 617110 // 38.8909 Hz
#define NOTE_D1 653806 // 36.7081 Hz
#define NOTE_C1S 692682 // 34.6479 Hz
#define NOTE_C1 733873 // 32.7032 Hz
#define NOTE_B0 777511 // 30.8677 Hz
#define NOTE_A0S 823743 // 29.1353 Hz
#define NOTE_A0 872727 // 27.5000 Hz


//*****************************************************************************
// DO NOT MODIFY ANYTHING BELOW
//*****************************************************************************
#define MEASURE_DURATION 12000000    // 500 milliseconds
#define MEASURE_RATIO           4    // 2/4 time
#define DELAY_AMOUNT       240000    // 10  milliseconds
#define SONG_NUM_NOTES 31

extern TaskHandle_t Task_Buzzer_Handle;

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
void Task_Buzzer(void);

#endif /* TASK_BUZZER_H_ */
