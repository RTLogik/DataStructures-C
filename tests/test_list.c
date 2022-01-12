#include "unity_fixture.h"
#include "list.h"
#include <stdint.h>

TEST_GROUP(linked_list);

List_t list;
typedef uint32_t ItemType[3];

TEST_SETUP(linked_list)
{
    //List_Init(&list, 10, NULL);
}

TEST_TEAR_DOWN(linked_list)
{
    //List_Delete(list);
}

void AddRemovePeekTest(List_t list);

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

TEST(linked_list, AddPeekRemoveSinglyNotCircular)
{
    List_Init(&list, sizeof(ItemType), SINGLY | NOT_CIRCULAR);

    AddRemovePeekTest(list);
}

TEST(linked_list, AddPeekRemoveSinglyCircular)
{
    List_Init(&list, sizeof(ItemType), SINGLY | CIRCULAR);

    AddRemovePeekTest(list);
}

TEST(linked_list, AddPeekRemoveDoublyNotCircular)
{
    List_Init(&list, sizeof(ItemType), DOUBLY | NOT_CIRCULAR);

    AddRemovePeekTest(list);
}

TEST(linked_list, AddPeekRemoveDoublyCircular)
{
    List_Init(&list, sizeof(ItemType), DOUBLY | CIRCULAR);

    AddRemovePeekTest(list);
}

TEST(linked_list, ListSearch)
{
    List_Init(&list, sizeof(int), DOUBLY | CIRCULAR);

    int item[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    for (int i = 0; i < sizeof item; i++) {
        List_Add_Last(list, &item[i]);
    }

    int item2 = 15;
    TEST_ASSERT_EQUAL_INT(4, List_IndexOf(list, &item[3]));
    TEST_ASSERT_EQUAL_INT(-1, List_IndexOf(list, &item2));
}

void AddRemovePeekTest(List_t list)
{
    ItemType array1 = {1, 2, 3};
    ItemType array2 = {4, 5, 6};
    ItemType array3 = {7, 8, 9};
    ItemType array4 = {10, 11, 12};
    ItemType array5 = {13, 14, 15};
    ItemType array;



    TEST_ASSERT_EQUAL_INT(LIST_EMPTY, List_Peek_First(list, array));
    TEST_ASSERT_EQUAL_INT(LIST_EMPTY, List_Peek_Last(list, array));
    TEST_ASSERT_EQUAL_INT(LIST_EMPTY, List_Remove_First(list, array));
    TEST_ASSERT_EQUAL_INT(LIST_EMPTY, List_Remove_Last(list, array));

    /* Populate the list in all the possible ways */
    TEST_ASSERT_EQUAL_INT(LIST_OK, List_Add_First(list, array1));    // 1
    TEST_ASSERT_EQUAL_INT(LIST_OK, List_Add_Last(list, array2));     // 1-2
    TEST_ASSERT_EQUAL_INT(LIST_OK, List_Add_First(list, array3));    // 3-1-2
    TEST_ASSERT_EQUAL_INT(LIST_OK, List_Add_Last(list, array4));     // 3-1-2-4
    TEST_ASSERT_EQUAL_INT(LIST_OK, List_Add_After(list, array5, 1)); // 3-5-1-2-4
    TEST_ASSERT_EQUAL_INT(LIST_INDEX_ERROR, List_Add_After(list, array5, 6));

    /* Peek tests */
    TEST_ASSERT_EQUAL_INT(LIST_OK, List_Peek_First(list, array));
    TEST_ASSERT_EQUAL_INT(array3[0], array[0]);
    TEST_ASSERT_EQUAL_INT(array3[1], array[1]);
    TEST_ASSERT_EQUAL_INT(array3[2], array[2]);

    TEST_ASSERT_EQUAL_INT(LIST_OK, List_Peek_Last(list, array));
    TEST_ASSERT_EQUAL_INT(array4[0], array[0]);
    TEST_ASSERT_EQUAL_INT(array4[1], array[1]);
    TEST_ASSERT_EQUAL_INT(array4[2], array[2]);

    TEST_ASSERT_EQUAL_INT(LIST_OK, List_Peek_Index(list, array, 2));
    TEST_ASSERT_EQUAL_INT(array5[0], array[0]);
    TEST_ASSERT_EQUAL_INT(array5[1], array[1]);
    TEST_ASSERT_EQUAL_INT(array5[2], array[2]);

    TEST_ASSERT_EQUAL_INT(LIST_OK, List_Peek_Index(list, array, 3));
    TEST_ASSERT_EQUAL_INT(array1[0], array[0]);
    TEST_ASSERT_EQUAL_INT(array1[1], array[1]);
    TEST_ASSERT_EQUAL_INT(array1[2], array[2]);

    TEST_ASSERT_EQUAL_INT(LIST_OK, List_Peek_Index(list, array, 1));
    TEST_ASSERT_EQUAL_INT(array3[0], array[0]);
    TEST_ASSERT_EQUAL_INT(array3[1], array[1]);
    TEST_ASSERT_EQUAL_INT(array3[2], array[2]);

    TEST_ASSERT_EQUAL_INT(LIST_OK, List_Peek_Index(list, array, 5));
    TEST_ASSERT_EQUAL_INT(array4[0], array[0]);
    TEST_ASSERT_EQUAL_INT(array4[1], array[1]);
    TEST_ASSERT_EQUAL_INT(array4[2], array[2]);

    TEST_ASSERT_EQUAL_INT(LIST_INDEX_ERROR, List_Peek_Index(list, array, 6));

    /* Remove tests */
    TEST_ASSERT_EQUAL_INT(LIST_INDEX_ERROR, List_Remove_Index(list, array, 6));

    TEST_ASSERT_EQUAL_INT(LIST_OK, List_Remove_First(list, array));
    TEST_ASSERT_EQUAL_INT(array3[0], array[0]);
    TEST_ASSERT_EQUAL_INT(array3[1], array[1]);
    TEST_ASSERT_EQUAL_INT(array3[2], array[2]);

    TEST_ASSERT_EQUAL_INT(LIST_OK, List_Remove_Index(list, array, 3));
    TEST_ASSERT_EQUAL_INT(array2[0], array[0]);
    TEST_ASSERT_EQUAL_INT(array2[1], array[1]);
    TEST_ASSERT_EQUAL_INT(array2[2], array[2]);

    TEST_ASSERT_EQUAL_INT(LIST_OK, List_Remove_First(list, array));
    TEST_ASSERT_EQUAL_INT(array5[0], array[0]);
    TEST_ASSERT_EQUAL_INT(array5[1], array[1]);
    TEST_ASSERT_EQUAL_INT(array5[2], array[2]);

    TEST_ASSERT_EQUAL_INT(LIST_OK, List_Remove_Last(list, array));
    TEST_ASSERT_EQUAL_INT(array4[0], array[0]);
    TEST_ASSERT_EQUAL_INT(array4[1], array[1]);
    TEST_ASSERT_EQUAL_INT(array4[2], array[2]);

    TEST_ASSERT_EQUAL_INT(LIST_OK, List_Remove_Last(list, array));
    TEST_ASSERT_EQUAL_INT(array1[0], array[0]);
    TEST_ASSERT_EQUAL_INT(array1[1], array[1]);
    TEST_ASSERT_EQUAL_INT(array1[2], array[2]);

    /* A few extra corner cases */
    TEST_ASSERT_EQUAL_INT(LIST_OK, List_Add_After(list, array1, 0)); // 1
    TEST_ASSERT_EQUAL_INT(LIST_OK, List_Add_After(list, array2, 1)); // 1-2
    TEST_ASSERT_EQUAL_INT(LIST_OK, List_Add_After(list, array3, 2)); // 1-2-3

    TEST_ASSERT_EQUAL_INT(LIST_OK, List_Peek_Index(list, array, 1));
    TEST_ASSERT_EQUAL_INT(array1[0], array[0]);
    TEST_ASSERT_EQUAL_INT(array1[1], array[1]);
    TEST_ASSERT_EQUAL_INT(array1[2], array[2]);

    TEST_ASSERT_EQUAL_INT(LIST_OK, List_Peek_Index(list, array, 2));
    TEST_ASSERT_EQUAL_INT(array2[0], array[0]);
    TEST_ASSERT_EQUAL_INT(array2[1], array[1]);
    TEST_ASSERT_EQUAL_INT(array2[2], array[2]);

    TEST_ASSERT_EQUAL_INT(LIST_OK, List_Peek_Index(list, array, 3));
    TEST_ASSERT_EQUAL_INT(array3[0], array[0]);
    TEST_ASSERT_EQUAL_INT(array3[1], array[1]);
    TEST_ASSERT_EQUAL_INT(array3[2], array[2]);

    TEST_ASSERT_EQUAL_INT(LIST_OK, List_Remove_Index(list, array, 1));
    TEST_ASSERT_EQUAL_INT(array1[0], array[0]);
    TEST_ASSERT_EQUAL_INT(array1[1], array[1]);
    TEST_ASSERT_EQUAL_INT(array1[2], array[2]);

    TEST_ASSERT_EQUAL_INT(LIST_OK, List_Remove_Index(list, array, 2));
    TEST_ASSERT_EQUAL_INT(array3[0], array[0]);
    TEST_ASSERT_EQUAL_INT(array3[1], array[1]);
    TEST_ASSERT_EQUAL_INT(array3[2], array[2]);

    TEST_ASSERT_EQUAL_INT(LIST_OK, List_Remove_Index(list, array, 1));
    TEST_ASSERT_EQUAL_INT(array2[0], array[0]);
    TEST_ASSERT_EQUAL_INT(array2[1], array[1]);
    TEST_ASSERT_EQUAL_INT(array2[2], array[2]);

    List_Delete(list);
}