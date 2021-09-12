#include "datastructs.h"

typedef enum {STATIC, DYNAMIC} QueueType_e;

struct QueueStruct {
    int  length;
    int *base;
    int *tail;
    int *head;
    QueueType_e queueType;
};

/* Check if pointers are valid */
static QueueStatus_e Queue_Check(Queue_t buffer)
{
    if ( ! buffer || ! buffer->head || ! buffer->tail || ! buffer->base) {
        return QUEUE_NULL;
    }
    return QUEUE_OK;
}

QueueStatus_e Queue_Init(Queue_t *bufferPtr, int length, int *memory)
{
    if (length > MAX_QUEUE_SIZE)
        return QUEUE_LENGTH_ERROR;

    *bufferPtr = malloc(sizeof(struct QueueStruct));
    (*bufferPtr)->length = length;

    if (memory == NULL) {
        (*bufferPtr)->base = malloc(sizeof(int) * length);
        if ( ! (*bufferPtr)->base ) 
            return STACK_INIT_ERROR; 
        (*bufferPtr)->queueType = DYNAMIC;
    } else {
        (*bufferPtr)->base = memory;
        (*bufferPtr)->queueType = STATIC;
    }

    (*bufferPtr)->head = (*bufferPtr)->base;
    (*bufferPtr)->tail = (*bufferPtr)->base;

    return STACK_OK;
}

void Queue_Delete(Queue_t buffer)
{
    if (buffer->queueType == DYNAMIC) {
        free(buffer->base);
    }
    free(buffer);
}

QueueStatus_e Queue_Is_Full(Queue_t buffer)
{
    // Check for errors:
    QueueStatus_e status = Queue_Check(buffer);
    if (status != QUEUE_OK) 
        return QUEUE_NULL;

    if ( (buffer->tail == buffer->head + 1) ||
         (buffer->head == buffer->tail + (buffer->length - 1)) ) {
        return QUEUE_FULL;
    } else {
        return QUEUE_NOT_FULL;
    }
}

QueueStatus_e Queue_Is_Empty(Queue_t buffer)
{
    // Check for errors:
    QueueStatus_e status = Queue_Check(buffer);
    if (status != QUEUE_OK) 
        return QUEUE_NULL;

    if (buffer->tail == buffer->head) {
        return QUEUE_FULL;
    } else {
        return QUEUE_NOT_FULL;
    }
}

QueueStatus_e Queue_Add(Queue_t buffer, int item2add)
{
    // Check if buffer is full:
    QueueStatus_e check = Queue_Is_Full(buffer);
    if (check != QUEUE_NOT_FULL) 
        return check;

    if ( buffer->head == buffer->head + (buffer->length -1) ) {
        buffer->head = buffer->base;
    } else {
        buffer->head++;
    }

    *(buffer->head) = item2add;

    return QUEUE_OK;
}

QueueStatus_e Queue_Remove(Queue_t buffer, int *item2remove)
{
    // Check if buffer is empty:
    QueueStatus_e check = Queue_Is_Empty(buffer);
    if (check != QUEUE_NOT_EMPTY) 
        return check;
    
    *item2remove = *(buffer->head);

    if ( buffer->tail == buffer->tail + (buffer->length -1) ) {
        buffer->tail = buffer->base;
    } else {
        buffer->tail++;
    }
    
    return QUEUE_OK;
}