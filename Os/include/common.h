#ifndef COMMON_H_
#define COMMON_H_
#include <time.h>
/********************************************************************************
 * Constant Definitions
 *******************************************************************************/

/// @brief Arbitrary number of temporary strings
#define MAX_LENGTH_OF_STRING    81
///  @brief Macros to report function results
#define SUCCESS                 0
#define FAILURE                 -1
#define EXIT_LOOP               1
#define TRUE 1
#define FALSE 0

#define TICK_VAL        100

/// @brief Enum used in functions to return empty/not empty values
typedef enum {
    NOT_EMPTY,
    EMPTY

}systemErrors_t;

/// @brief Enum for specifying the queue what kind of data is being sent
typedef enum {
    DATE,
    HOUR
}messageType_t;

/**
 * @brief message to be used for intercomunicate both tasks
*/
typedef struct _Message
{
    uint8_t msg;
    uint8_t hour;
    uint8_t minutes;
    uint8_t seconds;
    uint8_t day;
    uint8_t wday;
    uint8_t month;
    uint16_t year;
} Message;

#if 0
#define ENABLE_DEBUG_MESSAGES
#endif


#ifdef  ENABLE_DEBUG_MESSAGES
#define PRINT_PARAMS(value,...)             printf( #value "\n",## __VA_ARGS__);
#define PRINT(value)                        printf( #value "\n");
#define DEBUG(value)                        value
#else
#define PRINT_PARAMS(value,...) 
#define PRINT(value)
#define DEBUG(value)
#endif

#endif /* __BUFFER_H */