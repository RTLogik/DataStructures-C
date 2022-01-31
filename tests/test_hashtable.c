#include "unity_fixture.h"
#include "hashtable.h"

TEST_GROUP(hashtable);

HashTable_t table;

typedef struct {
    char city[20];
    int age;
    // ...
} ValueType_t;

TEST_SETUP(hashtable)
{
    //Stack_Init(&buffer, 10, NULL);
}

TEST_TEAR_DOWN(hashtable)
{
    //Stack_Delete(buffer);
}

TEST(hashtable, InitializeTable)
{
    TEST_ASSERT_EQUAL_INT(HASHTABLE_OK, HashTable_Init(&table));
}

TEST(hashtable, InsertAndGet)
{
    TEST_ASSERT_EQUAL_INT(HASHTABLE_OK, HashTable_Init(&table));

    int antonio_value = 24;
    int pablo_value = 24;

    int *pInteger;

    TEST_ASSERT_EQUAL_INT(HASHTABLE_OK, HashTable_Insert(table, "Antonio", &antonio_value, sizeof(int)));
    TEST_ASSERT_EQUAL_INT(HASHTABLE_OK, HashTable_Insert(table, "Pablo", &pablo_value, sizeof(int)));

    TEST_ASSERT_EQUAL_INT(HASHTABLE_OK, HashTable_Get(table, "Antonio", &pInteger));
    TEST_ASSERT_EQUAL_INT(antonio_value, *pInteger);

    TEST_ASSERT_EQUAL_INT(HASHTABLE_OK, HashTable_Get(table, "Pablo", &pInteger));
    TEST_ASSERT_EQUAL_INT(pablo_value, *pInteger);

    TEST_ASSERT_EQUAL_INT(HASHTABLE_NO_ENTRY, HashTable_Get(table, "Pedro", &pInteger));
}

TEST(hashtable, InsertAndRemove)
{
    TEST_ASSERT_EQUAL_INT(HASHTABLE_OK, HashTable_Init(&table));

    int antonio_value = 24;
    int pablo_value = 24;

    int *pInteger;

    TEST_ASSERT_EQUAL_INT(HASHTABLE_OK, HashTable_Insert(table, "Antonio", &antonio_value, sizeof(int)));
    TEST_ASSERT_EQUAL_INT(HASHTABLE_OK, HashTable_Insert(table, "Pablo", &pablo_value, sizeof(int)));

    // TEST_ASSERT_EQUAL_INT(HASHTABLE_OK, HashTable_Remove(table, "Antonio"));
    // TEST_ASSERT_EQUAL_INT(HASHTABLE_NO_ENTRY, HashTable_Get(table, "Antonio", &pInteger));

    // TEST_ASSERT_EQUAL_INT(HASHTABLE_OK, HashTable_Remove(table, "Pablo"));
    // TEST_ASSERT_EQUAL_INT(HASHTABLE_NO_ENTRY, HashTable_Get(table, "Pablo", &pInteger));
}

TEST(hashtable, InsertAndRemoveWithCollisions)
{
    TEST_ASSERT_EQUAL_INT(HASHTABLE_OK, HashTable_Init(&table));

    int antonio_value = 24;
    int pablo_value = 24;

    int *pInteger;

    TEST_ASSERT_EQUAL_INT(HASHTABLE_OK, HashTable_Insert(table, "Antonio", &antonio_value, sizeof(int)));
    TEST_ASSERT_EQUAL_INT(HASHTABLE_OK, HashTable_Insert(table, "Pablo", &pablo_value, sizeof(int)));

    TEST_ASSERT_EQUAL_INT(HASHTABLE_OK, HashTable_Remove(table, "Antonio"));
    TEST_ASSERT_EQUAL_INT(HASHTABLE_NO_ENTRY, HashTable_Get(table, "Antonio", &pInteger));

    TEST_ASSERT_EQUAL_INT(HASHTABLE_OK, HashTable_Remove(table, "Pablo"));
    TEST_ASSERT_EQUAL_INT(HASHTABLE_NO_ENTRY, HashTable_Get(table, "Antonio", &pInteger));
}

