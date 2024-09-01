/**
 * \file buffer.c
 * 
 * Functions call necessary for the circular buffer. The circular buffer will
 * store a specific amount of values and it is operated by a FIFO logic.
 * 
*/

/********************************************************************************
 * Header Files
 *******************************************************************************/

#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <string.h>
#include "queue.h"
#include "common.h"

/********************************************************************************
 * Variable Declarations
 *******************************************************************************/

/********************************************************************************
 * Private Function Prototypes
 *******************************************************************************/

/********************************************************************************
 * Public Function
 *******************************************************************************/

void Queue_initQueue( Queue_Queue_t* queue ) {
    queue->Empty      = TRUE;
    queue->Full       = FALSE;
    queue->Head       = 0;
    queue->Tail       = 0;
}

uint8_t Queue_writeData( Queue_Queue_t* queue, void *data ) {
    uint8_t* ptrActualPos = queue->Buffer;
    uint8_t* ptrToWrite = NULL;
    // check if queue is full
    if ( queue->Full == TRUE ) {
        printf( "\n   Queue is full! \n\n   " );
        return FALSE;      
    } else {
        ptrToWrite = ptrActualPos + (queue->Tail * queue->Size);
        queue->Empty = FALSE;
        memcpy(ptrToWrite, data, sizeof((queue->Size)*queue->Elements));
        queue->Tail++;
        if ( queue->Tail == queue->Elements ) {
            queue->Full = TRUE;
            queue->Tail = 0;
            queue->Head = 0;
        }
        return TRUE;
    }           
}

uint8_t Queue_readData( Queue_Queue_t* queue, void* data ) {
    uint8_t* ptrActualPos = queue->Buffer;
    uint8_t* ptrToRead = NULL;

    if ( queue->Empty == FALSE ) {
        ptrToRead = ptrActualPos + (queue->Head * queue->Size);
        memcpy(data, ptrToRead, sizeof((queue->Size)*queue->Elements));
        queue->Head++;         //   Increase position to prepare for next read
    } else {
        return FALSE;
    }
    // if at last index in buffer, set read Index back to 0 
    if ( queue->Head == queue->Elements ) {
        queue->Empty = TRUE;
        queue->Head = 0;
        queue->Tail = 0;
    }
    return TRUE;
}

uint8_t Queue_isQueueEmpty( Queue_Queue_t* queue ) {
    if ( queue->Empty == TRUE ) {
        printf( "\n\t\t\t\t\t\t\t|\t\t\t\t\t|\n\t\t\t\t\t\t\t|\tqueue is empty!\t\t\t|\n   " );
        return EMPTY;
    } 
    return NOT_EMPTY;
}

void Queue_flushQueue( Queue_Queue_t* queue ) {
    queue->Empty = TRUE;
    queue->Head = 0;
    queue->Tail = 0;
    queue->Buffer = NULL;
}

//TODO test functions isbuffer empty and readData
/********************************************************************************
 * Private Function Definitions
 *******************************************************************************/



