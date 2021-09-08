/*
 * lifo.c by rtlogik
 */

#include "datastruct.h"

struct LIFO{
    int  length;
    int *base;
    int *head;
};

/* Check if pointers are valid */
static LIFO_Status LIFO_Check(LIFO_t *lbuf)
{
    if ( ! lbuf || ! lbuf->head || ! lbuf->base ) {
        return LIFO_NULL;
    }
    return LIFO_OK;
}

LIFO_Status LIFO_Init(LIFO_t *lbuf, int length) 
{
    lbuf->length = length;
    lbuf->base = malloc(sizeof(int) * length);
    if ( ! lbuf->base ) { return LIFO_INIT_ERROR; }
    lbuf->head = lbuf->base;
    return LIFO_OK;
}

LIFO_Status LIFO_Is_Full(LIFO_t *lbuf)
{
    // Check for errors:
    LIFO_Status status = LIFO_Check(lbuf);
    if (status != LIFO_OK) 
        return LIFO_NULL;

    if (lbuf->head >= (lbuf->base + lbuf->length)) 
        return LIFO_FULL;
    else 
        return LIFO_NOT_FULL;
}

LIFO_Status LIFO_Is_Empty(LIFO_t *lbuf)
{
    // Check for errors:
    LIFO_Status status = LIFO_Check(lbuf);
    if (status != LIFO_OK) 
        return LIFO_NULL;

    if (lbuf->base == lbuf->head) 
        return LIFO_EMPTY;
    else 
        return LIFO_NOT_EMPTY;
}

LIFO_Status LIFO_Push(LIFO_t *lbuf, int item2push) 
{
    // Check if buffer is full: (refactorizar)
    LIFO_Status fullCheck = LIFO_Is_Full(lbuf);
    if ( LIFO_Is_Full(lbuf) != LIFO_NOT_FULL ) 
        return fullCheck;
        
    *(lbuf->head) = item2push; 
    lbuf->head++;
    return LIFO_OK;
}

LIFO_Status LIFO_Pop(LIFO_t *lbuf, int *item2pop)
{
    // Check if buffer is empty: (refactorizar)
    LIFO_Status emptyCheck = LIFO_Is_Empty(lbuf);
    if ( LIFO_Is_Empty(lbuf) != LIFO_NOT_EMPTY ) 
        return emptyCheck;

    lbuf->head--;
    *item2pop = *(lbuf->head);
    return LIFO_OK;
}

LIFO_Status LIFO_Delete(LIFO_t *lbuf)
{
    free(lbuf->base);
}
