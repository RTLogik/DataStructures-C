/**
 * @file queue.h
 * @author rtlogik - contact@rtlogik.com
 * @brief Queue Interface Header
 * 
 */

#ifndef _QUEUE_H_
#define _QUEUE_H_

/**
 * Defines the maximum size of the queue buffer
 */
#define MAX_QUEUE_SIZE 100

/**
 * @brief Queue Status Enumeration
 * 
 * This enumeration is used as a return value for all of the functions
 * 
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


typedef struct QueueStruct *Queue_t;

/************** QUEUE INTERFACE **************/
QueueStatus_e Queue_Init(Queue_t *bufferPtr, int length, int *memory); 
void Queue_Delete(Queue_t buffer);  
QueueStatus_e Queue_Clear(Queue_t buffer);          
QueueStatus_e Queue_Is_Full(Queue_t buffer);
QueueStatus_e Queue_Is_Empty(Queue_t buffer);
QueueStatus_e Queue_Add(Queue_t buffer, int item2add);
QueueStatus_e Queue_Remove(Queue_t buffer, int *item2remove);
QueueStatus_e Queue_Peek_Index(Queue_t buffer, int *item2peek, int index);
QueueStatus_e Queue_Peek(Queue_t buffer, int *item2peek);
int Queue_Size(Queue_t buffer);

#endif /* _QUEUE_H_ */