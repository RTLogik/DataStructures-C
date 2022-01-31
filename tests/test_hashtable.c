#include "unity_fixture.h"
#include "hashtable.h"

TEST_GROUP(hashtable);

HashTable_t table;

typedef struct {
    char city[20];
    int age;
    // ...
} PersonType_t;

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
    TEST_ASSERT_EQUAL_INT(HASHTABLE_OK, HashTable_Init(&table, sizeof(PersonType_t)));
}

TEST(hashtable, InsertAndGet)
{
    TEST_ASSERT_EQUAL_INT(HASHTABLE_OK, HashTable_Init(&table, sizeof(PersonType_t)));

    PersonType_t antonio = {.city = "Murcia", .age = 24};
    PersonType_t pablo   = {.city = "Sevilla", .age = 32};

    PersonType_t item;

    TEST_ASSERT_EQUAL_INT(HASHTABLE_OK, HashTable_Insert(table, "Antonio", &antonio));
    TEST_ASSERT_EQUAL_INT(HASHTABLE_OK, HashTable_Insert(table, "Pablo", &pablo));

    TEST_ASSERT_EQUAL_INT(HASHTABLE_OK, HashTable_Get(table, "Antonio", &item));
    TEST_ASSERT_EQUAL_MEMORY(&antonio, &item, sizeof(PersonType_t));

    TEST_ASSERT_EQUAL_INT(HASHTABLE_OK, HashTable_Get(table, "Pablo", &item));
    TEST_ASSERT_EQUAL_MEMORY(&pablo, &item, sizeof(PersonType_t));

    TEST_ASSERT_EQUAL_INT(HASHTABLE_NO_ENTRY, HashTable_Get(table, "Pedro", &item));
}

TEST(hashtable, InsertAndRemove)
{
    TEST_ASSERT_EQUAL_INT(HASHTABLE_OK, HashTable_Init(&table, sizeof(PersonType_t)));

    int antonio_value = 24;
    int pablo_value = 24;

    int *pInteger;

    TEST_ASSERT_EQUAL_INT(HASHTABLE_OK, HashTable_Insert(table, "Antonio", &antonio_value));
    TEST_ASSERT_EQUAL_INT(HASHTABLE_OK, HashTable_Insert(table, "Pablo", &pablo_value));

    // TEST_ASSERT_EQUAL_INT(HASHTABLE_OK, HashTable_Remove(table, "Antonio"));
    // TEST_ASSERT_EQUAL_INT(HASHTABLE_NO_ENTRY, HashTable_Get(table, "Antonio", &pInteger));

    // TEST_ASSERT_EQUAL_INT(HASHTABLE_OK, HashTable_Remove(table, "Pablo"));
    // TEST_ASSERT_EQUAL_INT(HASHTABLE_NO_ENTRY, HashTable_Get(table, "Pablo", &pInteger));
}

TEST(hashtable, InsertAndRemoveWithCollisions)
{
    TEST_ASSERT_EQUAL_INT(HASHTABLE_OK, HashTable_Init(&table, sizeof(PersonType_t)));

    int antonio_value = 24;
    int pablo_value = 24;

    int *pInteger;

    TEST_ASSERT_EQUAL_INT(HASHTABLE_OK, HashTable_Insert(table, "Antonio", &antonio_value));
    TEST_ASSERT_EQUAL_INT(HASHTABLE_OK, HashTable_Insert(table, "Pablo", &pablo_value));

    TEST_ASSERT_EQUAL_INT(HASHTABLE_OK, HashTable_Remove(table, "Antonio"));
    TEST_ASSERT_EQUAL_INT(HASHTABLE_NO_ENTRY, HashTable_Get(table, "Antonio", &pInteger));

    TEST_ASSERT_EQUAL_INT(HASHTABLE_OK, HashTable_Remove(table, "Pablo"));
    TEST_ASSERT_EQUAL_INT(HASHTABLE_NO_ENTRY, HashTable_Get(table, "Antonio", &pInteger));
}

