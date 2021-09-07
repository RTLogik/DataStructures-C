/**
 * @file lifo.h
 * @author rtlogik (contact@rtlogik.com)
 * @brief LIFO (Last-In-First-Out)
 * @version 0.1
 * @date 2021-09-07
 * 
 * 
 */

#ifndef _LIFO_H_
#define _LIFO_H_

/**
 * @brief LIFO Status
 * 
 * This enumeration is used as a return value for all of the functions
 * 
 */
typedef enum {
    LIFO_OK = 0,
    LIFO_WIDTH_ERROR,
    LIFO_INIT_ERROR,
    LIFO_EMPTY,
    LIFO_NOT_EMPTY,
    LIFO_FULL,
    LIFO_NOT_FULL,
    LIFO_NULL
} LIFO_Status;

typedef struct {
    size_t length;
    uint8_t width;
    void   *base;
    void   *head;
} LIFO_t;


/************** PUBLIC API FUNCTIONS **************/
LIFO_Status LIFO_Init(LIFO_t *lbuf);
LIFO_Status LIFO_Is_Full(LIFO_t *lbuf);
LIFO_Status LIFO_Is_Empty(LIFO_t *lbuf);
LIFO_Status LIFO_Push(LIFO_t *lbuf, uint32_t item2push);
LIFO_Status LIFO_Pop(LIFO_t *lbuf, uint32_t * item2pop);
LIFO_Status LIFO_Delete(LIFO_t *lbuf);

#endif /* _LIFO_H_ */