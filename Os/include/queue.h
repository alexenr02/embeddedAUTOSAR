#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdint.h>

/********************************************************************************
 * Constant Definitions
 *******************************************************************************/


/********************************************************************************
 * Data Prototypes
 *******************************************************************************/

/**
 * @brief Queue object. Contains all the information about the queue
*/
typedef struct {
    void            *Buffer;
    uint32_t        Elements;
    uint8_t         Size;
    uint8_t         Head;
    uint8_t         Tail;
    uint8_t         Empty;
    uint8_t         Full;
}Queue_Queue_t;

/********************************************************************************
 * External Functions Prototypes
 *******************************************************************************/
/**
 * @brief Function to initialize the queue with zero values
 * 
 * \param queue  pointer to the queue structure
 * 
 * \return void
 * 
 */
void Queue_initQueue( Queue_Queue_t* queue );

/**
 * @brief Function to write data of any type in the queue
 * 
 * \param queue pointer to the queue structure
 * \param data  pointer to the data will be inserted in the queue  
 * 
 * \return  True if the write was successful
 * 
 */
uint8_t Queue_writeData( Queue_Queue_t* queue, void *data );

/**
 * @brief Function to read a data from the queue
 * 
 * \param  queue pointer to the queue structure
 * \param  data  pointer to the data where the data read will be stored
 * 
 * \return True if the read was successful
 * 
 */
uint8_t Queue_readData( Queue_Queue_t* queue, void *data );

/**
 * @brief Function to determine if the queue is empty
 * 
 * \param queue pointer to the queue structure
 * 
 * \return True if queue is empty
 * 
 */
uint8_t Queue_isQueueEmpty( Queue_Queue_t* queue );


/**
 * @brief Function to delete all the elements in the queue
 * 
 * \param queue pointer to the queue structure
 * 
 * \return void
 * 
 */
void Queue_flushQueue( Queue_Queue_t* queue );

#endif /* __QUEUE_H */