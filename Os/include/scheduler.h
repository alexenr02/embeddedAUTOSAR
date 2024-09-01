#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include <stdint.h>

/********************************************************************************
 * Constant Definitions
 *******************************************************************************/


/********************************************************************************
 * Data Prototypes
 *******************************************************************************/
/**
 * @brief Struct that contains the data pointers for the functions and data values needed for their execution 
 * in the scheduler
*/
typedef struct _task {
    uint32_t        period;
    uint32_t        elapsed;
    uint8_t         startFlag;
    uint8_t         taskId;
    void            (*initFunc) (void);
    void            (*taskFunc) (void);
}Sched_Task_t;

/**
 * @brief Struct that contains the data pointer for the callback function and data values needed for their execution
 * of the timer
*/
typedef struct _AppSched_Timer {
    uint32_t        timeout;                /* Timer timeout to decrement and reload when the timer is re-started */
    uint32_t        count;                  /* Actual timer decrement count */
    uint8_t         startFlag;              /* Flag to start timer count */
    uint8_t         runFlag;
    void            (*callbackPtr)(void);   /* Pointer to callback function */
} Sched_Timer_t;

/**
 * @brief Struct that contains all the information about the tasks and timers suscribed to the scheduler
*/
typedef struct {
    uint8_t         tasks;                  /* Number of tasks to handle */
    uint32_t        tick;                   /* Time base in ms */
    uint32_t        timeout;                /* Number of milliseconds the scheduler should run */
    uint8_t         tasksCount;             /* Internal task counter */
    Sched_Task_t    *taskPtr;               /* Pointer to buffer for the TCB tasks */
    uint8_t         timers;                 /* Number of software timer to use */
    Sched_Timer_t   *timerPtr;              /* Pointer to buffer timer array */
    uint8_t         timersCount;            /* Number of software timers registered */
} Sched_Scheduler_t;




/********************************************************************************
 * External Functions Prototypes
 *******************************************************************************/
/**
 * @brief Function to initialize the scheduler
 * 
 * \param scheduler pointer to the scheduler structure that contains all the information about tasks and timers
 * \param tasks     number of tasks that the scheduler will handle
 * \param tick      tick value time in ms
 * \param timeout   value of time that determines the end of scheduler execution
 * \param taskPtr   pointer to the task structure
 * \param timers    number of timers that the scheduler will handle
 * \param timerPtr pointer to the timer structure
 * 
 * \return none
 */
void Sched_initScheduler ( Sched_Scheduler_t* scheduler, uint8_t tasks, uint32_t tick, uint32_t timeout, Sched_Task_t* taskPtr, uint8_t timers, Sched_Timer_t *timerPtr );

/**
 * @brief Function to register a task in the scheduler
 * 
 * \param  scheduler    pointer to the scheduler structure that contains all the information about tasks and timers
 * \param  initPtr      pointer to the init function of the task
 * \param  taskPtr      pointer to the task function
 * \param  period       value of the period that the task will be executing
 * 
 * \return  TRUE if the register was successful, otherwise FALSE
 * 
 */
uint8_t Sched_registerTask( Sched_Scheduler_t* scheduler, void (*initPtr)(void), void(*taskPtr)(void), uint32_t period );

/**
 * @brief Function that stops the execution of a task
 * 
 * \param  scheduler    pointer to the scheduler structure that contains all the information about tasks and timers
 * \param  task         id value of the task that will be stopped
 * 
 * \return TRUE if the stop was successful, otherwise FALSE
 * 
 */
uint8_t Sched_stopTask( Sched_Scheduler_t *scheduler, uint8_t task );

/**
 * @brief Function that starts the execution of a task
 * 
 * \param  scheduler    pointer to the scheduler structure that contains all the information about tasks and timers
 * \param  task         id value of the task that will be started 
 * 
 * \return TRUE if the start was successful, otherwise FALSE
 * 
 */
uint8_t Sched_startTask ( Sched_Scheduler_t *scheduler, uint8_t task );

/**
 * @brief Function to change the period of a task
 * 
 * \param  scheduler    pointer to the scheduler structure that contains all the information about tasks and timers
 * \param  task         id value of the task that will change its period 
 * \param  period       value of the new period
 *
 * \return TRUE if the change was successful, otherwise FALSE
 * 
 */
uint8_t Sched_periodicTask( Sched_Scheduler_t *scheduler, uint8_t task , uint32_t period );


/**
 * @brief Function to start the scheduler and launch all the tasks and timers
 * 
 * \param scheduler    pointer to the scheduler structure that contains all the information about tasks and timers
 * 
 * \return TRUE if the start was successful, otherwise FALSE
 * 
 */
uint8_t Sched_startScheduler( Sched_Scheduler_t *scheduler );

/**
 * @brief Function to register a timer in the scheduler
 * 
 * \param scheduler    pointer to the scheduler structure that contains all the information about tasks and timers
 * \param timeout      value of time counter that determines the end of the timer
 * \param callbackPtr  Pointer to callback function 
 * 
 * \return TRUE if the register was successful, otherwise FALSE
 * 
 */
uint8_t Sched_registerTimer( Sched_Scheduler_t *scheduler, uint32_t timeout, void (*callbackPtr)(void) );

/**
 * @brief Function to obtain the current timer count
 * 
 * \param scheduler     pointer to the scheduler structure that contains all the information about tasks and timers
 * \param timer         id value of the timer
 * 
 * \return TRUE if the time was obtained successfully, otherwise FALSE
 * 
 */
uint8_t Sched_getTimer( Sched_Scheduler_t *scheduler, uint8_t timer );

/**
 * @brief Function to reload the timer count of a scheduler timer
 * 
 * \param scheduler     pointer to the scheduler structure that contains all the information about tasks and timers
 * \param timer         id value of the timer
 * \param timeout       value of time counter that determines the end of the timer
 * 
 * \return TRUE if the reload was successful, otherwise FALSE
 * 
 */
uint8_t Sched_reloadTimer( Sched_Scheduler_t *scheduler, uint8_t timer, uint32_t timeout );

/**
 * @brief Function to start a timer
 * 
 * \param scheduler     pointer to the scheduler structure that contains all the information about tasks and timers
 * \param timer         id value of the timer
 * 
 * \return TRUE if the start was successful, otherwise FALSE
 * 
 */
uint8_t Sched_startTimer( Sched_Scheduler_t *scheduler, uint8_t timer );

/**
 * @brief Function to stop a timer
 * 
 * \param scheduler     pointer to the scheduler structure that contains all the information about tasks and timers
 * \param timer         id value of the timer
 * 
 * \return TRUE if the stop was successful, otherwise FALSE
 * 
 */
uint8_t Sched_stopTimer( Sched_Scheduler_t *scheduler, uint8_t timer );


#endif /* __SCHEDULER_H */