
#include <stdlib.h>

#include "queue.h"

typedef enum {STATIC, DYNAMIC} QueueMemory_e;

struct QueueStruct {
    int  length;
    int  count;
    int *base;
    int *tail;
    int *head;
    QueueMemory_e queueMemory;
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
            return QUEUE_INIT_ERROR;
        (*bufferPtr)->queueMemory = DYNAMIC;
    } else {
        (*bufferPtr)->base = memory;
        (*bufferPtr)->queueMemory = STATIC;
    }

    (*bufferPtr)->head = (*bufferPtr)->base;
    (*bufferPtr)->tail = (*bufferPtr)->base;
    (*bufferPtr)->count = 0;

    return QUEUE_OK;
}

void Queue_Delete(Queue_t buffer)
{
    if (buffer->queueMemory == DYNAMIC) {
        free(buffer->base);
    }
    free(buffer);
}

void Queue_Clear(Queue_t buffer)
{
    buffer->head = buffer->base;
    buffer->tail = buffer->base;
    buffer->count = 0;
}

QueueStatus_e Queue_Is_Full(Queue_t buffer)
{
    // Check for errors:
    QueueStatus_e status = Queue_Check(buffer);
    if (status != QUEUE_OK)
        return QUEUE_NULL;

    if (buffer->count == buffer->length) {
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

    if (buffer->count == 0) {
        return QUEUE_EMPTY;
    } else {
        return QUEUE_NOT_EMPTY;
    }
}

QueueStatus_e Queue_Add(Queue_t buffer, int item2add)
{
    // Check if buffer is full:
    QueueStatus_e check = Queue_Is_Full(buffer);
    if (check != QUEUE_NOT_FULL)
        return check;

    *(buffer->head) = item2add;
    buffer->count++;

    if ( buffer->head == buffer->base + buffer->length ) {
        buffer->head = buffer->base;
    } else {
        buffer->head++;
    }

    return QUEUE_OK;
}

QueueStatus_e Queue_Remove(Queue_t buffer, int *item2remove)
{
    // Check if buffer is empty:
    QueueStatus_e check = Queue_Is_Empty(buffer);
    if (check != QUEUE_NOT_EMPTY)
        return check;

    *item2remove = *(buffer->tail);
    buffer->count--;

    if ( buffer->tail == buffer->base + buffer->length ) {
        buffer->tail = buffer->base;
    } else {
        buffer->tail++;
    }

    return QUEUE_OK;
}

QueueStatus_e Queue_Peek(Queue_t buffer, int *item2peek)
{
    // Check if buffer is empty:
    QueueStatus_e check = Queue_Is_Empty(buffer);
    if (check != QUEUE_NOT_EMPTY)
        return check;

    *item2peek = *(buffer->tail);

    return QUEUE_OK;
}

QueueStatus_e Queue_Peek_Index(Queue_t buffer, int *item2peek, int index)
{
    if (index > buffer->count) {
        return QUEUE_INDEX_ERROR;
    }
    else if ( buffer->tail + index > buffer->base + buffer->length ) {
        *item2peek = *(buffer->base + (buffer->length - index));
    } else {
        *item2peek = *(buffer->tail);
    }



    return QUEUE_OK;
}

int Queue_Size(Queue_t buffer)
{
    return buffer->count;
}