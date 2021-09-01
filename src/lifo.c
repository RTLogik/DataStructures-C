/*
 * lifo.c by rtlogik
 */

#include "datastr.h"

/* Check if pointers are valid */
inline LIFO_Status LIFO_Check(LIFO_t *lbuf)
{
    if (lbuf->width == 1) {
        if ( ! lbuf || ! (uint8_t *)lbuf->head || ! (uint8_t *)lbuf->base ) {
        return LIFO_NULL;
        }
    } else if (lbuf->width == 2) {
        if ( ! lbuf || ! (uint16_t *)lbuf->head || ! (uint16_t *)lbuf->base ) {
        return LIFO_NULL;
        }
    } else if (lbuf->width == 4) {
        if ( ! lbuf || ! (uint32_t *)lbuf->head || ! (uint32_t *)lbuf->base ) {
        return LIFO_NULL;
        }
    } 
}

LIFO_Status LIFO_Is_Full(LIFO_t *lbuf)
{
    // Check for errors:
    LIFO_Status errorCheck = LIFO_Check(lbuf);
    if (!errorCheck) 
        return errorCheck;

    if (lbuf->width == 1) {
        if ( (uint8_t *)lbuf->head >= ((uint8_t *)lbuf->base + lbuf->length - 1) ) {
            return LIFO_FULL;
        } else {
            return LIFO_NOT_FULL;
        }
    } else if (lbuf->width == 2) {
        if ( (uint16_t *)lbuf->head >= ((uint16_t *)lbuf->base + lbuf->length - 1) ) {
            return LIFO_FULL;
        } else {
            return LIFO_NOT_FULL;
        }
    } else if (lbuf->width == 4) {
        if ( (uint32_t *)lbuf->head >= ((uint32_t *)lbuf->base + lbuf->length - 1) ) {
            return LIFO_FULL;
        } else {
            return LIFO_NOT_FULL;
        }
    }

}

LIFO_Status LIFO_Is_Empty(LIFO_t *lbuf)
{
    /* Check for errors: */ 
    LIFO_Status errorCheck = LIFO_Check(lbuf);
    if (!errorCheck) 
        return errorCheck;

    if (lbuf->base == lbuf->head) 
        return LIFO_EMPTY;
    else 
        return LIFO_NOT_EMPTY;
}

LIFO_Status LIFO_Push(LIFO_t *lbuf, uint32_t item2push) 
{
    // Check if buffer is full:
    LIFO_Status fullCheck = LIFO_Is_Full(lbuf);
    if ( LIFO_Is_Full(lbuf) != LIFO_NOT_FULL ) 
        return fullCheck;

    if (lbuf->width == 1) {
        (uint8_t *)lbuf->head++;
        (*(uint8_t *)lbuf->head) = (uint8_t)item2push;
        return LIFO_OK;
    } else if (lbuf->width == 2) {
        (uint16_t *)lbuf->head++;
        (*(uint16_t *)lbuf->head) = (uint16_t)item2push;
        return LIFO_OK;
    } else if (lbuf->width == 4) {
        (uint32_t *)lbuf->head++;
        (*(uint32_t *)lbuf->head) = (uint32_t)item2push;
        return LIFO_OK;
    }
}

LIFO_Status LIFO_Pop(LIFO_t *lbuf, uint32_t *item2pop)
{
    // Check if buffer is empty:
    LIFO_Status emptyCheck = LIFO_Is_Empty(lbuf);
    if ( LIFO_Is_Empty(lbuf) != LIFO_NOT_EMPTY ) 
        return emptyCheck;

    if (lbuf->width == 1) {
        (*(uint8_t *)item2pop) = (*(uint8_t *)lbuf->head);
        return LIFO_OK;
    } else if (lbuf->width == 2) {
        (*(uint16_t *)item2pop) = (*(uint16_t *)lbuf->head);
        return LIFO_OK;
    } else if (lbuf->width == 4) {
        (*item2pop) = (*(uint32_t *)lbuf->head);
        return LIFO_OK;
    }
}

LIFO_Status LIFO_Init(LIFO_t *lbuf) 
{
    if (lbuf->width == 1) {
        lbuf->width = 1;
        lbuf->base = malloc(lbuf->length);
        if ( ! lbuf->base ) { return LIFO_INIT_ERROR; }
        lbuf->head = lbuf->base;
        return LIFO_OK;
    } else if (lbuf->width == 2) {
        lbuf->width = 2;
        lbuf->base = malloc(lbuf->length<<1);
        if ( ! lbuf->base ) { return LIFO_INIT_ERROR; }
        lbuf->head = lbuf->base;
        return LIFO_OK;
    } else if (lbuf->width == 4) {
        lbuf->width = 4;
        lbuf->base = malloc(lbuf->length<<2);
        if ( ! lbuf->base ) { return LIFO_INIT_ERROR; }
        lbuf->head = lbuf->base;
        return LIFO_OK;
    } else return LIFO_WIDTH_ERROR;
}

inline LIFO_Status LIFO_Delete(LIFO_t *lbuf)
{
    free(lbuf->base);
}