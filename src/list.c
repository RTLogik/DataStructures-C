/*
 * Created by rtlogik
 */

#include "datastructs.h"

typedef enum {SINGLY_CIRCULAR = 5,
              DOUBLY_CIRCULAR = 6,
              SINGLY_NOT_CIRCULAR = 9,
              DOUBLY_NOT_CIRCULAR = 10
              } ListType_e;

struct ListStruct {
    void *firstNode;
    void *lastNode;
    ListType_e listType;
};

struct SinglyNodeStruct {
    int  data;
    struct SinglyNodeStruct *next;
};

struct DoublyNodeStruct {
    int  data;
    struct DoublyNodeStruct *next;
    struct DoublyNodeStruct *previous;
};


ListStatus_e List_Init(List_t *listPtr, int listType) 
{
    *listPtr = malloc(sizeof(struct ListStruct));
    if ( ! (*listPtr) ) 
        return LIST_INIT_ERROR;

    if ( listType == SINGLY_CIRCULAR || listType == SINGLY_NOT_CIRCULAR ||
         listType == DOUBLY_CIRCULAR || listType == DOUBLY_NOT_CIRCULAR ) {
        (*listPtr)->listType = listType;
    } else {
        return LIST_INIT_ERROR;
    }
    
    return LIST_OK;
}

void List_Delete(List_t list)
{
    free(list);
}