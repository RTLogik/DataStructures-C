/**
 * @file stack.h
 * @author rtlogik - contact@rtlogik.com
 * @brief Stack Interface Header
 * 
 */

#ifndef _STACK_H_
#define _STACK_H_

/**
 * Defines the maximum size of the stack buffer
 */
#define MAX_STACK_SIZE 100

/**
 * @brief Stack Status Enumeration
 * 
 * This enumeration is used as a return value for all of the functions
 * 
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


typedef struct StackStruct *Stack_t;

/************** STACK INTERFACE **************/
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

#endif /* _STACK_H_ */