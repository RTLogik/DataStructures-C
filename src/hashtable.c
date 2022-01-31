/*
 * Created by agomez
 */

#include "hashtable.h"

#define DELETE_ME ((void *)0xFFFFFFFF)

struct TableEntry {
    char *key;
    void *item;
    struct TableEntry *next;
};

static unsigned int _Hash_(char *key);

HashTableStatus_e HashTable_Init(HashTable_t *tablePtr, int itemSize)
{
    if (itemSize > MAX_ITEM_SIZE)
        return HASHTABLE_SIZE_ERROR;

    // Allocate memory for the table:
    *tablePtr = malloc((MAX_TABLE_SIZE + 1) * sizeof(struct TableEntry));
    if (*tablePtr == NULL)
        return HASHTABLE_INIT_ERROR;

    // Empty each table entry:
    for (int i = 0; i < MAX_TABLE_SIZE; i++) {
        (*tablePtr)[i].key = NULL;
        (*tablePtr)[i].item = NULL;
        (*tablePtr)[i].next = NULL;
    }

    // Use additional entry at the end to store item size:
    (*tablePtr)[MAX_TABLE_SIZE].item = itemSize;

    return HASHTABLE_OK;
}

HashTableStatus_e HashTable_Insert(HashTable_t table, char *key, void *pItem)
{
    int itemSize = (int)table[MAX_TABLE_SIZE].item;
    HashTable_t tmp = table;

    unsigned int slot = _Hash_(key);

    // Search first for already existing entry
    while (table[slot].key != NULL) {
        // Check each key in the slot:
        if (strncmp(table[slot].key, key, MAX_KEY_LENGTH) == 0) {
            // Override old item:
            memcpy(table[slot].item, pItem, itemSize);
            break;
        }

        if (table[slot].next != NULL)
            table = table[slot].next;
        else
            break;
    }

    table = tmp; // Reset the table pointer

    // Check if the first entry is empty
    if (table[slot].item == NULL) {
            // Insert key name:
            table[slot].key = malloc(strlen(key));
            strncpy(table[slot].key, key, MAX_KEY_LENGTH);

            // Insert item in the table entry:
            table[slot].item = malloc(itemSize);
            memcpy(table[slot].item, pItem, itemSize);

    }

    // Search for garbage entry (item == DELETE_ME) or end of slot's linked list
    while (1) {
        if (table[slot].item == DELETE_ME) {
            // Insert key name:
            table[slot].key = realloc(table[slot].key, strlen(key));
            strncpy(table[slot].key, key, MAX_KEY_LENGTH);

            // Insert item in the table entry:
            table[slot].item = realloc(table[slot].item, itemSize);
            memcpy(table[slot].item, pItem, itemSize);

            break;
        } else if (table[slot].next != NULL) {
            table = table[slot].next;
        } else {
            // Create entry
            table[slot].next = malloc(sizeof(struct TableEntry));
            table = table[slot].next;

            // Insert key name:
            table[slot].key = malloc(strlen(key));
            strncpy(table[slot].key, key, MAX_KEY_LENGTH);

            // Insert item in the table entry:
            table[slot].item = malloc(itemSize);
            memcpy(table[slot].item, pItem, itemSize);

            // Set next to null (end of linked list)
            table[slot].next = NULL;

            break;
        }
    }

    return HASHTABLE_OK;
}

HashTableStatus_e HashTable_Get(HashTable_t table, char *key, void *pItem)
{
    struct TableEntry entry = table[_Hash_(key)];
    int itemSize = (int)table[MAX_TABLE_SIZE].item;

    if (entry.key == NULL)
        return HASHTABLE_NO_ENTRY;

    while (1) {
        if (strncmp(entry.key, key, MAX_KEY_LENGTH) == 0) {
            memcpy(pItem, entry.item, itemSize);
            return HASHTABLE_OK;
        } else if (entry.next != NULL) {
            entry = *(entry.next);
        } else {
            return HASHTABLE_NO_ENTRY;
        }
    }
}

HashTableStatus_e HashTable_Remove(HashTable_t table, char *key)
{
    struct TableEntry *entry = &table[_Hash_(key)];

    if (entry->key == NULL)
        return HASHTABLE_NO_ENTRY;

    while(1) {
        if (strncmp(entry->key, key, MAX_KEY_LENGTH) == 0) {
            free(entry->key);
            free(entry->item);

            // if (entry->next == NULL)
            //     free(entry);
            // else
                entry->key = DELETE_ME;

            return HASHTABLE_OK;
        } else if (entry->next != NULL) {
            entry = entry->next;
        } else { return HASHTABLE_NO_ENTRY; }
    }


}



static unsigned int _Hash_(char *key)
{
    int length = strnlen(key, MAX_KEY_LENGTH);
    unsigned int hashValue = 0;
    for (int i = 0; i < length; i++) {
        hashValue += key[i];
        hashValue = (hashValue * key[i]) % MAX_TABLE_SIZE;
    }
    return hashValue;
}