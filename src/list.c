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

typedef enum {FIRST,
              LAST
              } NodePosition_e;

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
static SNode Find_Penultimate(List_t list);
static DNode Create_DNode(void *pItem, int itemSize);
static ListStatus_e List_Add_Singly_NotCircular(List_t list, NodePosition_e pos, void *pItem);
static ListStatus_e List_Add_Singly_Circular(List_t list, NodePosition_e pos, void *pItem);
static ListStatus_e List_Add_Doubly_NotCircular(List_t list, NodePosition_e pos, void *pItem);
static ListStatus_e List_Add_Doubly_Circular(List_t list, NodePosition_e pos, void *pItem);


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

    (*listPtr)->itemSize  = itemSize;
    (*listPtr)->firstNode = NULL;
    (*listPtr)->lastNode  = NULL;

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

    /* Call function associated with list type */
    if (list->listType == SINGLY_NOT_CIRCULAR) {
        if (List_Add_Singly_NotCircular(list, FIRST, pItem) == LIST_NULL)
            return LIST_NULL;

    } else if (list->listType == SINGLY_CIRCULAR) {
        if (List_Add_Singly_Circular(list, FIRST, pItem) == LIST_NULL)
            return LIST_NULL;

    } else if (list->listType == DOUBLY_NOT_CIRCULAR) {
        if (List_Add_Doubly_NotCircular(list, FIRST, pItem) == LIST_NULL)
            return LIST_NULL;

    } else if (list->listType == DOUBLY_CIRCULAR) {
        if (List_Add_Doubly_Circular(list, FIRST, pItem) == LIST_NULL)
            return LIST_NULL;
    }

    return LIST_OK;
}

ListStatus_e List_Add_Last(List_t list, void *pItem)
{
    /* Check list size */
    if (List_Size(list) >= MAX_LIST_SIZE)
        return LIST_FULL;

    /* Call function associated with list type */
    if (list->listType == SINGLY_NOT_CIRCULAR) {
        if (List_Add_Singly_NotCircular(list, LAST, pItem) == LIST_NULL)
            return LIST_NULL;

    } else if (list->listType == SINGLY_CIRCULAR) {
        if (List_Add_Singly_Circular(list, LAST, pItem) == LIST_NULL)
            return LIST_NULL;

    } else if (list->listType == DOUBLY_NOT_CIRCULAR) {
        if (List_Add_Doubly_NotCircular(list, LAST, pItem) == LIST_NULL)
            return LIST_NULL;

    } else if (list->listType == DOUBLY_CIRCULAR) {
        if (List_Add_Doubly_Circular(list, LAST, pItem) == LIST_NULL)
            return LIST_NULL;
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

        SNode first = (SNode)list->firstNode;
        memcpy(pItem, first->item, list->itemSize);

    } else if (list->listType == DOUBLY_NOT_CIRCULAR ||
               list->listType == DOUBLY_CIRCULAR) {

        DNode first = (DNode)list->firstNode;
        memcpy(pItem, first->item, list->itemSize);
    }

    return LIST_OK;
}

ListStatus_e List_Peek_Last(List_t list, void *pItem)
{
    /* Check list size */
    if (List_Size(list) == 0)
        return LIST_EMPTY;

    if (list->listType == SINGLY_NOT_CIRCULAR ||
        list->listType == SINGLY_CIRCULAR) {

        SNode last = (SNode)list->lastNode;
        memcpy(pItem, last->item, list->itemSize);

    } else if (list->listType == DOUBLY_NOT_CIRCULAR ||
               list->listType == DOUBLY_CIRCULAR) {

        DNode last = (DNode)list->lastNode;
        memcpy(pItem, last->item, list->itemSize);
    }

    return LIST_OK;
}

ListStatus_e List_Remove_First(List_t list, void *pItem)
{
        /* Check list size */
    if (List_Size(list) == 0)
        return LIST_EMPTY;

    if (list->listType == SINGLY_NOT_CIRCULAR ||
        list->listType == SINGLY_CIRCULAR) {

        /*Save node item */
        SNode first = (SNode)list->firstNode;
        memcpy(pItem, first->item, list->itemSize);

        /* Update pointers */
        if (first->next == NULL) {
            list->firstNode = NULL;
            list->lastNode = NULL;
        } else {
            list->firstNode = first->next;
            if (list->listType == SINGLY_CIRCULAR) {
                SNode last = (SNode)list->lastNode;
                last->next = list->firstNode;
            }
        }

        free(first);

    } else if (list->listType == DOUBLY_NOT_CIRCULAR ||
               list->listType == DOUBLY_CIRCULAR) {

        /* Save node item */
        DNode first = (DNode)list->firstNode;
        memcpy(pItem, first->item, list->itemSize);

        /* Update pointers */
        if (first->next == NULL) {
            list->firstNode = NULL;
            list->lastNode = NULL;
        } else {
            DNode second = (DNode)first->next;
            if (list->listType == DOUBLY_CIRCULAR) {
                second->previous = list->lastNode;
                DNode last = (DNode)list->lastNode;
                last->next = second;
            } else {
                second->previous = NULL;
            }
            list->firstNode = second;
        }

        free(first);
    }

    return LIST_OK;
}

ListStatus_e List_Remove_Last(List_t list, void *pItem)
{
    /* Check list size */
    if (List_Size(list) == 0)
        return LIST_EMPTY;

    if (list->listType == SINGLY_NOT_CIRCULAR ||
        list->listType == SINGLY_CIRCULAR) {

        /* Save node item */
        SNode last = (SNode)list->lastNode;
        memcpy(pItem, last->item, list->itemSize);

        /* Update pointers */
        SNode penultimate = Find_Penultimate(list);
        list->lastNode = penultimate;
        if (list->listType == SINGLY_CIRCULAR) {
            penultimate->next = list->firstNode;
        } else {
            penultimate->next = NULL;
        }

        free(last);

    } else if (list->listType == DOUBLY_NOT_CIRCULAR ||
               list->listType == DOUBLY_CIRCULAR) {

        /* Save node item */
        DNode last = (DNode)list->lastNode;
        memcpy(pItem, last->item, list->itemSize);

        /* Update pointers */
        if (last->previous != NULL && last->previous != list->lastNode) {
            DNode penultimate = last->previous;
            list->lastNode = penultimate;
            if (list->listType == DOUBLY_CIRCULAR) {
                DNode first = list->firstNode;
                first->previous = penultimate;
                penultimate->next = first;
            } else {
                penultimate->next = NULL;
            }
        }

        free(last);
    }

    return LIST_OK;
}


static ListStatus_e List_Add_Singly_NotCircular(List_t list, NodePosition_e pos, void *pItem)
{
    /* Create a single pointer node */
    SNode newNode = Create_SNode(pItem, list->itemSize);
    if (!newNode)
        return LIST_NULL;

    /* Update pointers */
    if (list->firstNode == NULL) {     // Not initialized list
        newNode->next = NULL;
        list->lastNode = newNode;
        list->firstNode = newNode;
    } else if (pos == FIRST) {
        newNode->next = list->firstNode;
        list->firstNode = newNode;
    } else if (pos == LAST) {
        SNode last = list->lastNode;
        last->next = newNode;
        newNode->next = NULL;
        list->lastNode = newNode;
    }

    return LIST_OK;
}

static ListStatus_e List_Add_Singly_Circular(List_t list, NodePosition_e pos, void *pItem)
{
    /* Create a single pointer node */
    SNode newNode = Create_SNode(pItem, list->itemSize);
    if (!newNode)
        return LIST_NULL;

    /* Update pointers */
    if (list->firstNode == NULL) {    // Not initialized list
        newNode->next = newNode;
        list->firstNode = newNode;
        list->lastNode = newNode;
    } else {
        SNode last = list->lastNode;
        last->next = newNode;
        newNode->next = list->firstNode;
        if (pos == FIRST)
            list->firstNode = newNode;
        else if (pos == LAST)
            list->lastNode = newNode;
    }

    return LIST_OK;
}

static ListStatus_e List_Add_Doubly_NotCircular(List_t list, NodePosition_e pos, void *pItem)
{
    /* Create a double pointer node */
    DNode newNode = Create_DNode(pItem, list->itemSize);
    if (!newNode)
        return LIST_NULL;

    /* Update pointers */
    if (list->firstNode == NULL) {    // Not initialized list
        newNode->next = NULL;
        list->firstNode = newNode;
        list->lastNode = newNode;
    } else if (pos == FIRST) {
        DNode first = list->firstNode;
        first->previous = newNode;
        newNode->previous = NULL;
        newNode->next = first;
        list->firstNode = newNode;
    } else if (pos == LAST) {
        DNode last = list->lastNode;
        last->next = newNode;
        newNode->next = NULL;
        newNode->previous = last;
        list->lastNode = newNode;
    }

    return LIST_OK;
}

static ListStatus_e List_Add_Doubly_Circular(List_t list, NodePosition_e pos, void *pItem)
{
    /* Create a double pointer node */
    DNode newNode = Create_DNode(pItem, list->itemSize);
    if (!newNode)
        return LIST_NULL;

    /* Update pointers */
    if (list->firstNode == NULL) {    // Not initialized list
        newNode->next = NULL;
        newNode->previous = NULL;
        list->firstNode = newNode;
        list->lastNode = newNode;
    } else {
        DNode last = list->lastNode;
        DNode first = list->firstNode;
        last->next = newNode;
        first->previous = newNode;
        newNode->previous = list->lastNode;
        newNode->next = list->firstNode;
        if (pos == FIRST)
            list->firstNode = newNode;
        else if (pos == LAST)
            list->lastNode = newNode;
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

static SNode Find_Penultimate(List_t list)
{
    SNode node = list->firstNode;
    SNode previousNode = node;

    while (node != list->lastNode) {
        previousNode = node;
        node = node->next;
    }

    return previousNode;
}
