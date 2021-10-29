/**
 * @file list.h
 * @author rtlogik - contact@rtlogik.com
 * @brief Linked List Interface Header
 * 
 */

#ifndef DATASTRUCTS_LIST_H
#define DATASTRUCTS_LIST_H

/**
 * Defines the maximum size of the list
 */
#define MAX_LIST_SIZE 100

/**
 * Defines the maximum size (in bytes) of the items in the list
 */
#define MAX_ITEM_SIZE 64

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
    LIST_SIZE_ERROR,
    LIST_TYPE_ERROR,
    LIST_LENGTH_ERROR,
    LIST_EMPTY,
    LIST_NOT_EMPTY,
    LIST_FULL,
    LIST_NOT_FULL,
    LIST_NULL
} ListStatus_e;


typedef struct ListStruct *List_t;

/************** LIST INTERFACE **************/
ListStatus_e List_Init(List_t *listPtr, int itemSize, int listType); 
void List_Delete(List_t list);                      
ListStatus_e List_Add_First(List_t list, void *pItem);
ListStatus_e List_Add_Last(List_t list, void *pItem);
ListStatus_e List_Add_After(List_t list, void *pItem, int index);
ListStatus_e List_Remove_First(List_t list, void *pItem);
ListStatus_e List_Remove_Last(List_t list, void *pItem);
ListStatus_e List_Remove_Index(List_t list, void *pItem, int index);
ListStatus_e List_Peek_First(List_t list, void *pItem);
ListStatus_e List_Peek_Last(List_t list, void *pItem);
ListStatus_e List_Peek_Index(List_t list, void *pItem, int index);
int List_Size(List_t list);

#endif /* DATASTRUCTS_LIST_H */