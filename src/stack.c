#include "datastructs.h"

typedef enum {STATIC, DYNAMIC} StackType_e;

struct StackStruct {
    int  length;
    int *base;
    int *head;
    StackType_e stackType;
};

/* Check if pointers are valid */
static StackStatus_e Stack_Check(Stack_t buffer)
{
    if ( ! buffer || ! buffer->head || ! buffer->base ) {
        return STACK_NULL;
    }
    return STACK_OK;
}

StackStatus_e Stack_Init(Stack_t *bufferPtr, int length, int *memory) 
{
    if (length > MAX_STACK_SIZE)
        return STACK_LENGTH_ERROR;

    *bufferPtr = malloc(sizeof(struct StackStruct));
    (*bufferPtr)->length = length;

    if (memory == NULL) {
        (*bufferPtr)->base = malloc(sizeof(int) * length);
        if ( ! (*bufferPtr)->base ) 
            return STACK_INIT_ERROR; 
        (*bufferPtr)->stackType = DYNAMIC;
    } else {
        (*bufferPtr)->base = memory;
        (*bufferPtr)->stackType = STATIC;
    }

    (*bufferPtr)->head = (*bufferPtr)->base;

    return STACK_OK;
}

void Stack_Delete(Stack_t buffer)
{
    if (buffer->stackType == DYNAMIC) {
        free(buffer->base);
    }
    free(buffer);
}

void Stack_Clear(Stack_t buffer)
{
    buffer->head = buffer->base;
}

StackStatus_e Stack_Is_Full(Stack_t buffer)
{
    // Check for errors:
    StackStatus_e status = Stack_Check(buffer);
    if (status != STACK_OK) 
        return STACK_NULL;

    if (buffer->head >= (buffer->base + buffer->length)) 
        return STACK_FULL;
    else 
        return STACK_NOT_FULL;
}

StackStatus_e Stack_Is_Empty(Stack_t buffer)
{
    // Check for errors:
    StackStatus_e status = Stack_Check(buffer);
    if (status != STACK_OK) 
        return STACK_NULL;

    if (buffer->base == buffer->head) 
        return STACK_EMPTY;
    else 
        return STACK_NOT_EMPTY;
}

StackStatus_e Stack_Push(Stack_t buffer, int item2push) 
{
    // Check if buffer is full: 
    StackStatus_e check = Stack_Is_Full(buffer);
    if (check != STACK_NOT_FULL) 
        return check;
        
    *(buffer->head) = item2push; 
    buffer->head++;
    return STACK_OK;
}

StackStatus_e Stack_Pop(Stack_t buffer, int *item2pop)
{
    // Check if buffer is empty: 
    StackStatus_e check = Stack_Is_Empty(buffer);
    if (check != STACK_NOT_EMPTY) 
        return check;

    buffer->head--;
    *item2pop = *(buffer->head);
    return STACK_OK;
}

StackStatus_e Stack_Peek(Stack_t buffer, int *item2peek)
{
    // Check if buffer is empty: (refactorizar)
    StackStatus_e emptyCheck = Stack_Is_Empty(buffer);
    if ( Stack_Is_Empty(buffer) != STACK_NOT_EMPTY ) 
        return emptyCheck;

    *item2peek = *(buffer->head - 1);

    return STACK_OK;
}

StackStatus_e Stack_Peek_Index(Stack_t buffer, int *item2peek, int index)
{
    if (index >= Stack_Size(buffer)) {
        *item2peek = 0;
        return STACK_INDEX_ERROR;
    }
        
    *item2peek = *(buffer->base + index);

    return STACK_OK;
}

int Stack_Size(Stack_t buffer)
{
    return (buffer->head - buffer->base);
}