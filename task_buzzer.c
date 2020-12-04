/*
 * task_buzzer.c
 *
 * Author: Michael Sexton
 *
 */

#include <task_buzzer.h>
TaskHandle_t Task_Buzzer_Handle;

bool song_played = false;

//Note_t Song[] =
//{
//
//    {NOTE_C5,ONE_QUARTER,true},  // Tone, Time, Delay
//    {NOTE_F5,ONE_QUARTER,true},
//    {NOTE_C5,ONE_QUARTER,true},
//    {NOTE_A4,ONE_QUARTER,true},
//
//    {NOTE_C5,ONE_QUARTER,true},
//    {NOTE_F5,ONE_QUARTER,true},
//    {NOTE_C5,ONE_HALF,true},
//
//    {NOTE_C5,ONE_QUARTER,true},
//    {NOTE_F5,ONE_QUARTER,true},
//    {NOTE_C5,ONE_QUARTER,true},
//    {NOTE_F5,ONE_QUARTER,true},
//
//    {NOTE_A5,ONE_QUARTER,true},
//    {NOTE_G5,ONE_QUARTER,true},
//    {NOTE_F5,ONE_EIGTH,true},
//    {NOTE_E5,ONE_EIGTH,true},
//    {NOTE_D5,ONE_EIGTH,true},
//    {NOTE_C5S,ONE_EIGTH,true},
//
//    {NOTE_C5,ONE_QUARTER,true},
//    {NOTE_F5,ONE_QUARTER,true},
//    {NOTE_C5,ONE_QUARTER,true},
//    {NOTE_A4,ONE_QUARTER,true},
//
//    {NOTE_C5,ONE_QUARTER,true},
//    {NOTE_F5,ONE_QUARTER,true},
//    {NOTE_C5,ONE_HALF,true},
//
//    {NOTE_F5,ONE_QUARTER,true},
//    {NOTE_D5,ONE_EIGTH,true},
//    {NOTE_C5,ONE_QUARTER,true},
//    {NOTE_A4S,ONE_QUARTER,true},
//
//    {NOTE_A4,ONE_QUARTER,true},
//    {NOTE_G4,ONE_QUARTER,true},
//    {NOTE_F4,ONE_HALF,false}
//
//};

//Note_t Song[] =
//{
//
//    {NOTE_E5,ONE_QUARTER,true},  // Tone, Time, Delay
//    {NOTE_C5,ONE_EIGTH,true},
//    {NOTE_D5,ONE_EIGTH,true},
//    {NOTE_G5,ONE_EIGTH,true},
//
//    {NOTE_E5,ONE_EIGTH,true}, //
//    {NOTE_C5,ONE_EIGTH,true},
//    {NOTE_D5,ONE_EIGTH,true},
//    {NOTE_G5,ONE_EIGTH,true},
//
//    {NOTE_E5,ONE_EIGTH,true},
//    {NOTE_C5,ONE_EIGTH,true},
//    {NOTE_D5,ONE_EIGTH,true},
//    {NOTE_G5,ONE_EIGTH,true},
//
//    {NOTE_E5,ONE_QUARTER,true},
//    {NOTE_G5,ONE_QUARTER,true},
//    {NOTE_A5,ONE_EIGTH,true},
//    {NOTE_C6,ONE_EIGTH,true},
//
//    {NOTE_A6S,ONE_EIGTH,true},
//    {NOTE_G5S,ONE_EIGTH,true},
//    {NOTE_G5,ONE_EIGTH,true},
//    {NOTE_F5,ONE_EIGTH,true},
//
//    {NOTE_D5S,ONE_EIGTH,true},
//    {NOTE_D5,ONE_EIGTH,true},
//    {NOTE_C5,ONE_EIGTH,true},
//    {NOTE_A6S,ONE_QUARTER,true},
//
//    {NOTE_A6S,ONE_QUARTER,true},
//    {NOTE_A6,ONE_EIGTH,true},
//    {NOTE_G5,ONE_EIGTH,true},
//    {NOTE_E5,ONE_EIGTH,true},
//
//    {NOTE_A6,ONE_EIGTH,true},
//    {NOTE_G5,ONE_EIGTH,true},
//    {NOTE_E5,ONE_EIGTH,false}
//
//
//};

Note_t Song[] =
{
 {NOTE_C5,ONE_EIGTH,true},{NOTE_A5,ONE_EIGTH,true}, {NOTE_G5,ONE_EIGTH,false},
};

//***************************************************************
// This function returns how long an individual  notes is played
//***************************************************************
uint32_t buzzer_get_time_delay(measure_time_t time)
{
    uint32_t time_return = 0;

    time_return  = MEASURE_DURATION * MEASURE_RATIO;

    switch(time)
    {
        case ONE_QUARTER:
        {
            time_return  = time_return / 4;
            break;
        }
        case ONE_HALF:
        {
            time_return  = time_return / 2;
            break;
        }
        case ONE_EIGTH:
        {
            time_return  = time_return / 8;
            break;
        }
        case THREE_EIGTH:
        {
            time_return = time_return * 3;
            time_return  = time_return / 8;
            break;
        }
        default:
        {
            break;
        }
    }

    return time_return - DELAY_AMOUNT;

}
/*****************************************************
 * Changes Buzzer Period
 *
 * Parameters
 *      None
 * Returns
 *      None
 *****************************************************/
void Buzzer_Set_Period(uint16_t ticks_period)
{
    //Set the period of the timer.
    TIMER_A0->CCR[0] = ticks_period - 1;

    // Configure BUZZER Duty Cycle to 50%
    TIMER_A0->CCR[4] = (ticks_period/2)-1;

    // Configure TAO.4 for RESET/SET Mode
    TIMER_A0->CCTL[4] = TIMER_A_CCTLN_OUTMOD_7;

    // Select the master clock as the timer source
    TIMER_A0->CTL = TIMER_A_CTL_SSEL__SMCLK;

    // Clear the current Mode Control Bits
    TIMER_A0->CTL &= ~TIMER_A_CTL_MC_MASK;

    // Set Mode Control to UP and Clear the current count
    TIMER_A0->CTL |= TIMER_A_CTL_MC__UP | TIMER_A_CTL_CLR;
}
/*
 * Busy waits for a given number of SMCLK clock cycles
 *
 * Parameters
 *      ticks: Number of ticks to wait
 *
 * Returns
 *      None
 */
void T32_1_wait(uint32_t ticks)
{
    // Stop the timer
    TIMER32_1->CONTROL = 0;

    // Set the timer to be a 32-bit, one-shot
    TIMER32_1->CONTROL = TIMER32_CONTROL_ONESHOT | TIMER32_CONTROL_SIZE;

    // Set the load register
    TIMER32_1->LOAD = ticks;

    // Start the timer
    TIMER32_1->CONTROL |= TIMER32_CONTROL_ENABLE;

    // Wait until it reaches 0
    while(TIMER32_1->VALUE !=0)
    {

    }

}
//***************************************************************************
// Plays a single note of the song based on note_index.  After
// the note is played, there is an optional delay in between
// notes.
//
// Examples
// Song[note_index].period       -- Used to determine the period of the
//                                  PWM pulse.
//
// Song[note_index].time         -- 1/4 or 1/2 time note.  Call
//                                  music_get_time_delay() to determine how
//                                  long to play the note
//
// Song[note_index].delay        -- If true, add a period of silence for
//                                  DELAY_AMOUNT
//
//                                  If false, return without delaying.
//*************************************************************************
static void buzzer_play_note(uint16_t note_index)
{
    // Set the Buzzer period
    Buzzer_Set_Period(Song[note_index].period);
    // Wait for length of note
    T32_1_wait(buzzer_get_time_delay(Song[note_index].time));

    // If the note needs a delay wait
    if(Song[note_index].delay)
    {
        T32_1_wait(DELAY_AMOUNT);
    }
}

//***************************************************************
// Initializes the buzzer
//***************************************************************
void Task_Buzzer_Init(void)
{
    // Set P2.7 to be a GPIO OUTPUT Pin
    P2->DIR |= BIT7;

    // the TIMERA PWM controller will control the buzzer
    // P2.7 <--> TA0.4
    P2->SEL0 |= BIT7;
    P2->SEL1 &= ~BIT7;

    // Turn off TA0
    TIMER_A0->CTL =0;
}


void Buzzer_On(void){
    // Clear the current Mode Control Bits
    TIMER_A0->CTL &= ~TIMER_A_CTL_MC_MASK;

    // Set Mode Control to UP and Clear the current count
    TIMER_A0->CTL |= TIMER_A_CTL_MC__UP | TIMER_A_CTL_CLR;
}

void Buzzer_Off(void){
    // Turn off the timer
    TIMER_A0->CTL &= ~TIMER_A_CTL_MC_MASK;
}

bool Buzzer_Run_Status(void){
    if((TIMER_A0->CTL & TIMER_A_CTL_MC_MASK)== TIMER_A_CTL_MC__STOP)
        return false;
    else
        return true;
}



//***************************************************************
// Plays the song (loop through, playing each note)
// and then returns
//***************************************************************
void Task_Buzzer(void)
{

    while(1){
        // Cycle through each note in the array
        int i;
        if(song_played == false)
        {
            for(i = 0; i < 3; i++)
                {
                    buzzer_play_note(i);
                }
            song_played = true;
        }


        // Turn the Buzzer off once playing
        Buzzer_Off();
    }
}
