#include "unity_fixture.h"
#include "list.h"

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

TEST(linked_list, ListInitialize)
{
    TEST_ASSERT_EQUAL_INT(LIST_OK, List_Init(&list, SINGLY | CIRCULAR));
    List_Delete(list);
}

TEST(linked_list, ListInitializeWrong)
{
    TEST_ASSERT_EQUAL_INT(LIST_INIT_ERROR, List_Init(&list, 7));
    List_Delete(list);
}