/**
 * @file hasthtable.h
 * @author agomez - agomez@emberity.com
 * @brief Hash Table Interface Header
 *
 */

#ifndef DATASTRUCTS_HASHTABLE_H
#define DATASTRUCTS_HASHTABLE_H

/******************************************************************************
* Includes
*******************************************************************************/
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

/******************************************************************************
* Preprocessor Constants
*******************************************************************************/
/**
 * Defines the maximum size of the table (number of elements)
 */
#define MAX_TABLE_SIZE 20

/**
 * Defines the maximum size (in bytes) of the items in the table
 */
#define MAX_ITEM_SIZE 50

/**
 * Defines the maximum size (in bytes) of the keys used in the table
 */
#define MAX_KEY_LENGTH 20

/******************************************************************************
* Typedefs
*******************************************************************************/
/**
 * This typedef is used as a return value for (almost) all of the functions.
 * It provides detailed info about the function execution
 */
typedef enum {
    HASHTABLE_OK = 0,
    HASHTABLE_INIT_ERROR,
    HASHTABLE_SIZE_ERROR,
    HASHTABLE_NO_ENTRY,
    HASHTABLE_NULL
} HashTableStatus_e;

/**
 * List typedef for declaring an instance of a table.
 * Used as an input argument in all the table interface functions
 */
typedef struct TableEntry *HashTable_t;

/******************************************************************************
* Function Prototypes (Interface)
*******************************************************************************/
HashTableStatus_e HashTable_Init(HashTable_t *tablePtr, int itemSize);
HashTableStatus_e HashTable_Insert(HashTable_t table, char *key, void *pItem);
HashTableStatus_e HashTable_Get(HashTable_t table, char *key, void *pItem);
HashTableStatus_e HashTable_Remove(HashTable_t table, char *key);
void HashTable_Clear(HashTable_t table);
void HashTable_Delete(HashTable_t table);

#endif /* DATASTRUCTS_HASHTABLE_H */