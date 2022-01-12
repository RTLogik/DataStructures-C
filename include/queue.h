/**
 * @file queue.h
 * @author agomez - agomez@emberity.com
 * @brief Queue Interface Header
 *
 */

#ifndef DATASTRUCTS_QUEUE_H
#define DATASTRUCTS_QUEUE_H

/******************************************************************************
* Includes
*******************************************************************************/
#include <stdlib.h>

/******************************************************************************
* Preprocessor Constants
*******************************************************************************/
/**
 * Defines the maximum size of the queue buffer
 */
#define MAX_QUEUE_SIZE 100

/**
 * This typedef is used as a return value for (almost) all of the functions.
 * It provides detailed info about the function execution
 */
typedef enum {
    QUEUE_OK = 0,
    QUEUE_INIT_ERROR,
    QUEUE_LENGTH_ERROR,
    QUEUE_INDEX_ERROR,
    QUEUE_EMPTY,
    QUEUE_NOT_EMPTY,
    QUEUE_FULL,
    QUEUE_NOT_FULL,
    QUEUE_NULL
} QueueStatus_e;

/**
 * Queue typedef for declaring an instance of a queue.
 * Used as an input argument in all the queue interface functions
 */
typedef struct QueueStruct *Queue_t;

/******************************************************************************
* Function Prototypes (Interface)
*******************************************************************************/
QueueStatus_e Queue_Init(Queue_t *bufferPtr, int length, int *memory);
void Queue_Delete(Queue_t buffer);
void Queue_Clear(Queue_t buffer);
QueueStatus_e Queue_Is_Full(Queue_t buffer);
QueueStatus_e Queue_Is_Empty(Queue_t buffer);
QueueStatus_e Queue_Add(Queue_t buffer, int item2add);
QueueStatus_e Queue_Remove(Queue_t buffer, int *item2remove);
QueueStatus_e Queue_Peek_Index(Queue_t buffer, int *item2peek, int index);
QueueStatus_e Queue_Peek(Queue_t buffer, int *item2peek);
int Queue_Size(Queue_t buffer);

#endif /* DATASTRUCTS_QUEUE_H */