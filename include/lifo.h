/*
 * lifo.h
 * by rtlogik
 */

#ifndef _LIFO_H_
#define _LIFO_H_

/************** DATA TYPES **************/
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
    uint8_t LIFO_WIDTH;
    uint8_t length;
    void   *base;
    void   *head;
} LIFO_t;


/************** FUNCTION PROT. **************/
static inline LIFO_Status LIFO_Check(LIFO_t *lbuf);
LIFO_Status LIFO_Is_Full(LIFO_t *lbuf);
LIFO_Status LIFO_Is_Empty(LIFO_t *lbuf);
LIFO_Status LIFO_Push(LIFO_t *lbuf, uint32_t item2push);
LIFO_Status LIFO_Pop(LIFO_t *lbuf, uint32_t * item2pop);
LIFO_Status LIFO_Init(LIFO_t *lbuf, uint8_t width, uint8_t lenght);
static inline LIFO_Status LIFO_Delete(LIFO_t *lbuf);

#endif /* _LIFO_H_ */