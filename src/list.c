/*
 * Created by rtlogik
 */

#include <stdlib.h>
#include <string.h>

#include "list.h"

typedef enum {SINGLY_CIRCULAR = 5,
              DOUBLY_CIRCULAR = 6,
              SINGLY_NOT_CIRCULAR = 9,
              DOUBLY_NOT_CIRCULAR = 10
              } ListType_e;

struct ListStruct {
    void *firstNode;
    void *lastNode;
    int itemSize;
    ListType_e listType;
};

typedef struct SinglyNodeStruct {
    void *item;
    struct SinglyNodeStruct *next;
} *SNode;

typedef struct DoublyNodeStruct {
    void *item;
    struct DoublyNodeStruct *next;
    struct DoublyNodeStruct *previous;
} *DNode;

static SNode Create_SNode(void *pItem, int itemSize);
static DNode Create_DNode(void *pItem, int itemSize);

ListStatus_e List_Init(List_t *listPtr, int itemSize, int listType) 
{
    if (itemSize > MAX_ITEM_SIZE) 
        return LIST_SIZE_ERROR;

    *listPtr = malloc(sizeof(struct ListStruct));
    if (listPtr == NULL) 
        return LIST_INIT_ERROR;

    if ( listType == (SINGLY_CIRCULAR)     ||  
         listType == (DOUBLY_CIRCULAR)     || 
         listType == (SINGLY_NOT_CIRCULAR) || 
         listType == (DOUBLY_NOT_CIRCULAR) ) {
        (*listPtr)->listType = listType;
    } else {
        return LIST_TYPE_ERROR;
    }

    (*listPtr)->itemSize = itemSize;
    (*listPtr)->firstNode = NULL;
    (*listPtr)->lastNode = NULL;

    return LIST_OK;
}

void List_Delete(List_t list)
{
    free(list);
    // Memory leak if I dont free nodes first
}

ListStatus_e List_Add_First(List_t list, void *pItem)
{   
    /* Check list size */
    if (List_Size(list) >= MAX_LIST_SIZE)
        return LIST_FULL;

    if (list->listType == SINGLY_NOT_CIRCULAR) {
        
        SNode newNode = Create_SNode(pItem, list->itemSize);
        if (!newNode)
            return LIST_NULL;

        /* Update pointers */
        if (list->firstNode == NULL) {    // Not initialized list
            newNode->next = NULL;
            list->lastNode = newNode;
        } else {
            newNode->next = list->firstNode;
        }
        list->firstNode = newNode;
    
    } else if (list->listType == DOUBLY_NOT_CIRCULAR) {

        DNode newNode = Create_DNode(pItem, list->itemSize);
        if (!newNode)
            return LIST_NULL;

        /* Update pointers */
        newNode->previous = NULL;
        if (list->firstNode == NULL) {    // Not initialized list
            newNode->next = NULL;
            list->lastNode = newNode;
        } else {
            newNode->next = list->firstNode;
        }
        list->firstNode = newNode;
    
    } else if (list->listType == SINGLY_CIRCULAR) {

        SNode newNode = Create_SNode(pItem, list->itemSize);
        if (!newNode)
            return LIST_NULL;

        /* Update pointers */
        if (list->firstNode == NULL) {    // Not initialized list
            newNode->next = newNode;
            list->lastNode = newNode;
        } else {
            SNode last = list->lastNode;
            last->next = newNode;
            newNode->next = list->firstNode;
        }
        list->firstNode = newNode;
    
    } else if (list->listType == DOUBLY_CIRCULAR) {
        
        DNode newNode = Create_DNode(pItem, list->itemSize);
        if (!newNode)
            return LIST_NULL;

        /* Update pointers */
        if (list->firstNode == NULL) {    // Not initialized list
            newNode->next = NULL;
            newNode->previous = NULL;
            list->lastNode = newNode;
        } else {
            DNode last = list->lastNode;
            last->next = newNode;
            newNode->previous = list->lastNode;
            newNode->next = list->firstNode;
        }
        list->firstNode = newNode;
    } 

    return LIST_OK;
}

ListStatus_e List_Peek_First(List_t list, void *pItem)
{
    /* Check list size */
    if (List_Size(list) == 0)
        return LIST_EMPTY;

    if (list->listType == SINGLY_NOT_CIRCULAR || 
        list->listType == SINGLY_CIRCULAR) {
        
        SNode node = (SNode)list->firstNode;
        memcpy(pItem, node->item, list->itemSize);
    
    } else if (list->listType == DOUBLY_NOT_CIRCULAR ||
               list->listType == DOUBLY_CIRCULAR) {

        DNode node = (DNode)list->firstNode;
        memcpy(pItem, node->item, list->itemSize);
    }

    return LIST_OK;
}

int List_Size(List_t list) 
{
    // To implement
    return 1;
}

static SNode Create_SNode(void *pItem, int itemSize) 
{
    /* Allocate memory for new node */
    SNode newNode = malloc(sizeof(struct SinglyNodeStruct));
    if (!newNode) 
        return NULL; 

    /* Allocate memory for node item */
    newNode->item = malloc(itemSize);
    if (!newNode->item) 
        return NULL; 

    /* Copy the item in the memory recently allocated */
    memcpy(newNode->item, pItem, itemSize);

    return newNode;
}

static DNode Create_DNode(void *pItem, int itemSize) 
{
    /* Allocate memory for new node */
    DNode newNode = malloc(sizeof(struct DoublyNodeStruct));
    if (!newNode) 
        return NULL; 

    /* Allocate memory for node item */
    newNode->item = malloc(itemSize);
    if (!newNode->item) 
        return NULL; 

    /* Copy the item in the memory recently allocated */
    memcpy(newNode->item, pItem, itemSize);

    return newNode;
}