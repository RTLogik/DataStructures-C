/**
 * @file stack.h
 * @author agomez - agomez@emberity.com
 * @brief Stack Interface Header
 *
 */

#ifndef DATASTRUCTS_STACK_H
#define DATASTRUCTS_STACK_H

/******************************************************************************
* Includes
*******************************************************************************/
#include <stdlib.h>

/******************************************************************************
* Preprocessor Constants
*******************************************************************************/
/**
 * Defines the maximum size of the stack buffer
 */
#define MAX_STACK_SIZE 100

/******************************************************************************
* Typedefs
*******************************************************************************/
/**
 * This typedef is used as a return value for (almost) all of the functions.
 * It provides detailed info about the function execution
 */
typedef enum {
    STACK_OK = 0,
    STACK_INIT_ERROR,
    STACK_LENGTH_ERROR,
    STACK_INDEX_ERROR,
    STACK_EMPTY,
    STACK_NOT_EMPTY,
    STACK_FULL,
    STACK_NOT_FULL,
    STACK_NULL
} StackStatus_e;

/**
 * Stack typedef for declaring an instance of a stack.
 * Used as an input argument in all the stack interface functions
 */
typedef struct StackStruct *Stack_t;


/******************************************************************************
* Function Prototypes (Interface)
*******************************************************************************/
StackStatus_e Stack_Init(Stack_t *bufferPtr, int length, int *memory);
void Stack_Delete(Stack_t buffer);
void Stack_Clear(Stack_t buffer);
StackStatus_e Stack_Is_Full(Stack_t buffer);
StackStatus_e Stack_Is_Empty(Stack_t buffer);
StackStatus_e Stack_Push(Stack_t buffer, int item2push);
StackStatus_e Stack_Pop(Stack_t buffer, int *item2pop);
StackStatus_e Stack_Peek(Stack_t buffer, int *item2peek);
StackStatus_e Stack_Peek_Index(Stack_t buffer, int *item2peek, int index);
int Stack_Size(Stack_t buffer);

#endif /* DATASTRUCTS_STACK_H */