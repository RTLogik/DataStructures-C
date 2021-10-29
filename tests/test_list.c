#include "unity_fixture.h"
#include "list.h"
#include <stdint.h>

TEST_GROUP(linked_list);

List_t list;

TEST_SETUP(linked_list)
{
    //List_Init(&list, 10, NULL);
}

TEST_TEAR_DOWN(linked_list)
{
    //List_Delete(list);
}

TEST(linked_list, InitializeList)
{
    TEST_ASSERT_EQUAL_INT(LIST_OK, List_Init(&list, 5, SINGLY | CIRCULAR));
    List_Delete(list);
}

TEST(linked_list, InitializeListWrong)
{
    TEST_ASSERT_EQUAL_INT(LIST_TYPE_ERROR, List_Init(&list, 5, 7));
    TEST_ASSERT_EQUAL_INT(LIST_SIZE_ERROR, List_Init(&list, 65, SINGLY | CIRCULAR));
    List_Delete(list);
}

TEST(linked_list, AddAndPeekSinglyNotCircular)
{
    typedef uint32_t ItemType[3];
    ItemType array1 = {1, 2, 3};
    ItemType array2 = {4, 5, 6};
    ItemType array3 = {7, 8, 9};
    ItemType array4 = {10, 11, 12};
    ItemType array;

    List_Init(&list, sizeof(ItemType), SINGLY | NOT_CIRCULAR);

    //TEST_ASSERT_EQUAL_INT(LIST_EMPTY, List_Peek_First(list, array3));
    //TEST_ASSERT_EQUAL_INT(LIST_EMPTY, List_Peek_Last(list, array3));

    TEST_ASSERT_EQUAL_INT(LIST_OK, List_Add_First(list, array1));
    TEST_ASSERT_EQUAL_INT(LIST_OK, List_Add_Last(list, array2));
    TEST_ASSERT_EQUAL_INT(LIST_OK, List_Add_First(list, array3));
    TEST_ASSERT_EQUAL_INT(LIST_OK, List_Add_Last(list, array4));

    TEST_ASSERT_EQUAL_INT(LIST_OK, List_Peek_First(list, array));
    TEST_ASSERT_EQUAL_INT32(array3[0], array[0]);
    TEST_ASSERT_EQUAL_INT32(array3[1], array[1]);
    TEST_ASSERT_EQUAL_INT32(array3[2], array[2]);

    TEST_ASSERT_EQUAL_INT(LIST_OK, List_Peek_Last(list, array));
    TEST_ASSERT_EQUAL_INT32(array4[0], array[0]);
    TEST_ASSERT_EQUAL_INT32(array4[1], array[1]);
    TEST_ASSERT_EQUAL_INT32(array4[2], array[2]);
}
