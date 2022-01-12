/*
 * Created by agomez
 */

#include "list.h"

typedef enum {
    SINGLY_CIRCULAR = 5,
    DOUBLY_CIRCULAR = 6,
    SINGLY_NOT_CIRCULAR = 9,
    DOUBLY_NOT_CIRCULAR = 10
} ListType_e;

typedef enum {
    FIRST = 0,
    LAST  = -1
} NodePosition_e;

struct ListStruct {
    void *firstNode;
    void *lastNode;
    int itemSize;
    int listSize;
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

static SNode _Create_SNode(void *pItem, int itemSize);
static DNode _Create_DNode(void *pItem, int itemSize);
static SNode _Find_Penultimate(List_t list);
static ListStatus_e _List_Add(List_t list, NodePosition_e pos, void *pItem);
static ListStatus_e _Add_Singly_NotCircular_Node(List_t list, NodePosition_e pos, void *pItem);
static ListStatus_e _Add_Singly_Circular_Node(List_t list, NodePosition_e pos, void *pItem);
static ListStatus_e _Add_Doubly_NotCircular_Node(List_t list, NodePosition_e pos, void *pItem);
static ListStatus_e _Add_Doubly_Circular_Node(List_t list, NodePosition_e pos, void *pItem);
static inline void _Add_Node_NotInit(List_t list, void *node);
static inline void _Add_Node_Middle(List_t list, int pos, void *node);
static inline void _Fetch_Singly_Nodes(List_t list, int index, SNode *anterior, SNode *posterior);
static inline void _Fetch_Doubly_Nodes(List_t list, int index, DNode *anterior, DNode *posterior);

/* -------------- Function Definitions --------------------------*/
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

    (*listPtr)->listSize  = 0;
    (*listPtr)->itemSize  = itemSize;
    (*listPtr)->firstNode = NULL;
    (*listPtr)->lastNode  = NULL;

    return LIST_OK;
}

void List_Delete(List_t list)
{
    List_Clear(list);
    free(list);
}

void List_Clear(List_t list)
{
    SNode node, nextNode;
    nextNode = list->firstNode;
    for (int i = 0; i < list->listSize; i++) {
        node = nextNode;
        nextNode = node->next;
        free(node);
    }
    list->listSize = 0;
}

ListStatus_e List_Add_First(List_t list, void *pItem)
{
    return _List_Add(list, FIRST, pItem);
}

ListStatus_e List_Add_Last(List_t list, void *pItem)
{
    return _List_Add(list, LAST, pItem);
}

ListStatus_e List_Add_After(List_t list, void *pItem, int index)
{
    if (index < 0 || index > list->listSize)
        return LIST_INDEX_ERROR;
    else if (index == list->listSize)
        return _List_Add(list, LAST, pItem);
    else
        return _List_Add(list, index, pItem);
}

ListStatus_e List_Peek_First(List_t list, void *pItem)
{
    /* Check list size */
    if (list->listSize == 0)
        return LIST_EMPTY;

    if (list->listType == SINGLY_NOT_CIRCULAR || list->listType == SINGLY_CIRCULAR)
        memcpy(pItem, ((SNode)list->firstNode)->item, list->itemSize);
    else
        memcpy(pItem, ((DNode)list->firstNode)->item, list->itemSize);

    return LIST_OK;
}

ListStatus_e List_Peek_Last(List_t list, void *pItem)
{
    /* Check list size */
    if (list->listSize == 0)
        return LIST_EMPTY;

    if (list->listType == SINGLY_NOT_CIRCULAR || list->listType == SINGLY_CIRCULAR)
        memcpy(pItem, ((SNode)list->lastNode)->item, list->itemSize);
    else
        memcpy(pItem, ((DNode)list->lastNode)->item, list->itemSize);

    return LIST_OK;
}

ListStatus_e List_Peek_Index(List_t list, void *pItem, int index)
{
    /* Check index */
    if (index < 1 || index > list->listSize)
        return LIST_INDEX_ERROR;

    if (list->listType == SINGLY_NOT_CIRCULAR || list->listType == SINGLY_CIRCULAR) {
        SNode anterior, posterior;
        _Fetch_Singly_Nodes(list, index, &anterior, &posterior);
        memcpy(pItem, anterior->item, list->itemSize);
    } else {
        DNode anterior, posterior;
        _Fetch_Doubly_Nodes(list, index, &anterior, &posterior);
        memcpy(pItem, anterior->item, list->itemSize);
    }

    return LIST_OK;
}


ListStatus_e List_Remove_First(List_t list, void *pItem)
{
    /* Check list size */
    if (list->listSize == 0)
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

    list->listSize--;

    return LIST_OK;
}

ListStatus_e List_Remove_Last(List_t list, void *pItem)
{
    /* Check list size */
    if (list->listSize == 0)
        return LIST_EMPTY;

    if (list->listType == SINGLY_NOT_CIRCULAR ||
        list->listType == SINGLY_CIRCULAR) {

        /* Save node item */
        SNode last = (SNode)list->lastNode;
        memcpy(pItem, last->item, list->itemSize);

        /* Update pointers */
        SNode penultimate = _Find_Penultimate(list);
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

    list->listSize--;

    return LIST_OK;
}

ListStatus_e List_Remove_Index(List_t list, void *pItem, int index)
{
    /* Check list size */
    if (list->listSize == 0)
        return LIST_EMPTY;

    /* Check index */
    if (index < 1 || index > list->listSize)
        return LIST_INDEX_ERROR;

    if (index == 1)
        return List_Remove_First(list, pItem);
    else if (index == list->listSize)
        return List_Remove_Last(list, pItem);

    if (list->listType == SINGLY_NOT_CIRCULAR ||
        list->listType == SINGLY_CIRCULAR) {

        /*Save node item */
        SNode anterior, node, posterior;
        _Fetch_Singly_Nodes(list, index, &node, &posterior);
        memcpy(pItem, node->item, list->itemSize);

        /* Update pointers */
        _Fetch_Singly_Nodes(list, index-1, &anterior, &node);
        anterior->next = posterior;

        free(node);

    } else {

        /* Save node item */
        DNode anterior, node, posterior;
        _Fetch_Doubly_Nodes(list, index, &node, &posterior);
        memcpy(pItem, node->item, list->itemSize);

        /* Update pointers */
        _Fetch_Doubly_Nodes(list, index-1, &anterior, &node);
        anterior->next = posterior;
        posterior->previous = anterior;

        free(node);
    }

    list->listSize--;

    return LIST_OK;
}

int List_IndexOf(List_t list, void *pItem)
{
    SNode node = (SNode)list->firstNode;
    for (int i = 1; i <= list->listSize; i++) {
        if (memcmp(node->item, pItem, list->itemSize) == 0)
            return i;

        node = node->next;
    }

    return -1;
}

inline int List_Size(List_t list)
{
    return list->listSize;
}

static ListStatus_e _List_Add(List_t list, NodePosition_e pos, void *pItem)
{
    /* Check list size */
    if (list->listSize >= MAX_LIST_SIZE)
        return LIST_FULL;

    /* Call function associated with list type */
    if (list->listType == SINGLY_NOT_CIRCULAR) {
        if (_Add_Singly_NotCircular_Node(list, pos, pItem) == LIST_NULL)
            return LIST_NULL;

    } else if (list->listType == SINGLY_CIRCULAR) {
        if (_Add_Singly_Circular_Node(list, pos, pItem) == LIST_NULL)
            return LIST_NULL;

    } else if (list->listType == DOUBLY_NOT_CIRCULAR) {
        if (_Add_Doubly_NotCircular_Node(list, pos, pItem) == LIST_NULL)
            return LIST_NULL;

    } else if (list->listType == DOUBLY_CIRCULAR) {
        if (_Add_Doubly_Circular_Node(list, pos, pItem) == LIST_NULL)
            return LIST_NULL;
    }

    return LIST_OK;
}

static ListStatus_e _Add_Singly_NotCircular_Node(List_t list, NodePosition_e pos, void *pItem)
{
    /* Create a single pointer node */
    SNode newNode = _Create_SNode(pItem, list->itemSize);
    if (!newNode)
        return LIST_NULL;

    /* Update pointers */
    if (list->firstNode == NULL) {     // Not initialized list
        _Add_Node_NotInit(list, newNode);
    } else if (pos == FIRST) {
        newNode->next = list->firstNode;
        list->firstNode = newNode;
    } else if (pos == LAST) {
        ((SNode)list->lastNode)->next = newNode;
        newNode->next = NULL;
        list->lastNode = newNode;
    } else {
        _Add_Node_Middle(list, pos, newNode);
    }

    list->listSize++;

    return LIST_OK;
}

static ListStatus_e _Add_Singly_Circular_Node(List_t list, NodePosition_e pos, void *pItem)
{
    /* Create a single pointer node */
    SNode newNode = _Create_SNode(pItem, list->itemSize);
    if (!newNode)
        return LIST_NULL;

    /* Update pointers */
    if (list->firstNode == NULL) {    // Not initialized list
        _Add_Node_NotInit(list, newNode);
    } else if (pos != FIRST && pos != LAST) {
        _Add_Node_Middle(list, pos, newNode);
    } else {
        ((SNode)list->lastNode)->next = newNode;
        newNode->next = list->firstNode;
        if (pos == FIRST)
            list->firstNode = newNode;
        else if (pos == LAST)
            list->lastNode = newNode;
    }

    list->listSize++;

    return LIST_OK;
}

static ListStatus_e _Add_Doubly_NotCircular_Node(List_t list, NodePosition_e pos, void *pItem)
{
    /* Create a double pointer node */
    DNode newNode = _Create_DNode(pItem, list->itemSize);
    if (!newNode)
        return LIST_NULL;

    /* Update pointers */
    if (list->firstNode == NULL) {    // Not initialized list
        _Add_Node_NotInit(list, newNode);
    } else if (pos == FIRST) {
        ((DNode)list->firstNode)->previous = newNode;
        newNode->previous = NULL;
        newNode->next = (DNode)list->firstNode;
        list->firstNode = newNode;
    } else if (pos == LAST) {
        ((DNode)list->lastNode)->next = newNode;
        newNode->next = NULL;
        newNode->previous = (DNode)list->lastNode;
        list->lastNode = newNode;
    } else {
        _Add_Node_Middle(list, pos, newNode);
    }

    list->listSize++;

    return LIST_OK;
}

static ListStatus_e _Add_Doubly_Circular_Node(List_t list, NodePosition_e pos, void *pItem)
{
    /* Create a double pointer node */
    DNode newNode = _Create_DNode(pItem, list->itemSize);
    if (!newNode)
        return LIST_NULL;

    /* Update pointers */
    if (list->firstNode == NULL) {    // Not initialized list
        _Add_Node_NotInit(list, newNode);
    } else if (pos != FIRST && pos != LAST) {
        _Add_Node_Middle(list, pos, newNode);
    }else {
        ((DNode)list->lastNode)->next = newNode;
        ((DNode)list->firstNode)->previous = newNode;
        newNode->previous = list->lastNode;
        newNode->next = list->firstNode;
        if (pos == FIRST)
            list->firstNode = newNode;
        else if (pos == LAST)
            list->lastNode = newNode;
    }

    list->listSize++;

    return LIST_OK;
}

static SNode _Create_SNode(void *pItem, int itemSize)
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

static DNode _Create_DNode(void *pItem, int itemSize)
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

static SNode _Find_Penultimate(List_t list)
{
    SNode node = list->firstNode;
    SNode previousNode = node;

    while (node != list->lastNode) {
        previousNode = node;
        node = node->next;
    }

    return previousNode;
}

static inline void _Add_Node_NotInit(List_t list, void *node)
{
    if (list->listType == SINGLY_NOT_CIRCULAR ||
        list->listType == SINGLY_CIRCULAR) {
        ((SNode)node)->next = NULL;
        list->firstNode = node;
        list->lastNode = node;
    } else {
        ((DNode)node)->next = NULL;
        ((DNode)node)->previous = NULL;
        list->firstNode = node;
        list->lastNode = node;
    }
}

static inline void _Add_Node_Middle(List_t list, int pos, void *node)
{
    if (list->listType == SINGLY_NOT_CIRCULAR ||
        list->listType == SINGLY_CIRCULAR) {
        SNode anterior;
        SNode posterior;
        _Fetch_Singly_Nodes(list, pos, &anterior, &posterior);
        anterior->next = node;
        ((SNode)node)->next = posterior;
    } else {
        DNode anterior;
        DNode posterior;
        _Fetch_Doubly_Nodes(list, pos, &anterior, &posterior);
        anterior->next = node;
        posterior->previous = node;
        ((DNode)node)->previous = anterior;
        ((DNode)node)->next = posterior;
    }
}

static void _Fetch_Singly_Nodes(List_t list, int index, SNode *anterior, SNode *posterior)
{
    *anterior = list->firstNode;
    *posterior = list->firstNode;
    for (int i = 0; i < index; i++) {
        *anterior = *posterior;
        *posterior = (*anterior)->next;
    }
}

static void _Fetch_Doubly_Nodes(List_t list, int index, DNode *anterior, DNode *posterior)
{
    *anterior = list->firstNode;
    *posterior = list->firstNode;
    for (int i = 0; i < index; i++) {
        *anterior = *posterior;
        *posterior = (*anterior)->next;
    }
}

