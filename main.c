/*! \file main.c
 *  \brief file that contains the main program.
 *
 *  This file contains main(), general structs, init functions, task functions and callbacks.
 *  This program runs a couple of tasks and timers and verify that the tasks can run correctly 
 *  and sharing information with the timers using a queue.
 */

#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include "common.h"
#include "scheduler.h"
#include "queue.h"
#include "rtc.h"
#include "Mcu.h"
#include "Port.h"
#include "Dio.h"
#include "Osif.h"

void EcuM_Init( void );

#define TASKS_N         2

#define TIMERS_N        0

static Sched_Task_t         tasks_array[ TASKS_N ];
static Sched_Scheduler_t    Sche;
static Rtcc_Clock_t         rtccClock;
static Queue_Queue_t        rtccQueue;
static Sched_Timer_t        timers[ TIMERS_N ];


void Init_500ms(void);
void Task_500ms(void);
void Init_1000ms(void);
void Task_1000ms(void);
int main( void )
{
    unsigned char TaskId;
    EcuM_Init();

    /*init the scheduler with two tasks and a tick time of 1ms */
    Sched_initScheduler( &Sche, TASKS_N, TICK_VAL, 0, tasks_array, TIMERS_N, NULL_PTR );

    /*register two task with thier corresponding init fucntions and their periodicyt, 100ms and 500ms*/
    if ( Sched_registerTask( &Sche, Init_500ms, Task_500ms, 500 ) == FALSE ) {
        printf("\nError: Could not register task.\n");
        return 0;
    }

    /*register two task with thier corresponding init fucntions and their periodicyt, 100ms and 500ms*/
    if ( Sched_registerTask( &Sche, Init_1000ms, Task_1000ms, 1000 ) == FALSE ) {
        printf("\nError: Could not register task.\n");
        return 0;
    }
    
    /*run the scheduler for the mount of time stablished in Sche.timeout*/
    Sched_startScheduler( &Sche );

    return 0;
}

void EcuM_Init( void )
{
    Mcu_Init( &Mcu_Config );
    /* Initialize the clock tree with no PLL active*/
    Mcu_InitClock( McuClockSettingConfig_0 );
    Mcu_SetMode( McuModeSettingConf_0 );
    /*Init the internal tick reference Systick Timer*/
    OsIf_Init( NULL_PTR );
    /*Apply all the Pin Port microcontroller configuration, for this case
    only Port Pin 96  (D0) is configured as output*/
    Port_Init( &Port_Config );
}

/**
 * @brief   Init task for 500ms task
 *
 * Print a message to the console to indicate that the task is running
*/
void Init_500ms(void)
{
    //printf("Init task 500 millisecond\n");
}

void Init_1000ms(void)
{

}

/**
 * @brief   500ms task
 *
 * 
*/
void Task_500ms(void)
{
    /*toggle led*/
    Dio_FlipChannel( DioConf_DioChannel_D15_RED_LED  );
}

void Task_1000ms(void)
{
    /*toggle led*/
    Dio_FlipChannel( DioConf_DioChannel_D0_BLUE_LED  );
}