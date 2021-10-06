/**
 * @file list.h
 * @author rtlogik - contact@rtlogik.com
 * @brief Linked List Interface Header
 * 
 */

#ifndef _LIST_H_
#define _LIST_H_

/**
 * Defines the maximum size of the list
 */
#define MAX_LIST_SIZE 100

#define SINGLY       (0x01)
#define DOUBLY       (0x01 << 1)
#define CIRCULAR     (0x01 << 2)
#define NOT_CIRCULAR (0x01 << 3)

/**
 * @brief List Status Enumeration
 * 
 * This enumeration is used as a return value for all of the functions
 * 
 */
typedef enum {
    LIST_OK = 0,
    LIST_INIT_ERROR,
    LIST_LENGTH_ERROR,
    LIST_EMPTY,
    LIST_NOT_EMPTY,
    LIST_FULL,
    LIST_NOT_FULL,
    LIST_NULL
} ListStatus_e;


typedef struct ListStruct *List_t;

/************** LIST INTERFACE **************/
ListStatus_e List_Init(List_t *listPtr, int listType); 
void List_Delete(List_t list);            
ListStatus_e List_Is_Full(List_t list);
ListStatus_e List_Is_Empty(List_t list);
ListStatus_e List_Add_First(List_t list, int item2add);
ListStatus_e List_Add_Last(List_t list, int item2add);
ListStatus_e List_Add_After(List_t list, int item2add, int index);
ListStatus_e List_Remove_First(List_t list, int *item2remove);
ListStatus_e List_Remove_Last(List_t list, int *item2remove);
ListStatus_e List_Remove_Index(List_t list, int *item2remove, int index);
ListStatus_e List_Peek(List_t list, int *item2peek);
ListStatus_e List_Peek_Index(List_t list, int *item2peek, int index);
int List_Size(List_t list);

#endif /* _LIST_H_ */