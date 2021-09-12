#include "unity_fixture.h"
#include "queue.h"

TEST_GROUP(queue);

Queue_t buffer;

TEST_SETUP(queue)
{
    //Queue_Init(&buffer, 10, NULL);
}

TEST_TEAR_DOWN(queue)
{
    //Queue_Delete(buffer);
}

TEST(queue, InitializeQueueDynamically)
{
    TEST_ASSERT_EQUAL_INT(QUEUE_OK, Queue_Init(&buffer, 10, NULL));
    Queue_Delete(buffer);
}

TEST(queue, InitializeQueueDynamicallyWrong)
{
    TEST_ASSERT_EQUAL_INT(QUEUE_LENGTH_ERROR, 
                          Queue_Init(&buffer, MAX_QUEUE_SIZE+1, NULL));
}

TEST(queue, InitializeQueueStatically)
{
    int memory[20];
    Queue_t buffer;
    TEST_ASSERT_EQUAL_INT(QUEUE_OK, Queue_Init(&buffer, 20, memory));
    Queue_Delete(buffer);
}

TEST(queue, AddRemoveQueueDynamically)
{
    int item;

    Queue_Init(&buffer, 10, NULL);

    Queue_Add(buffer, 1);
    Queue_Add(buffer, 2);
    Queue_Add(buffer, 3);

    Queue_Remove(buffer,&item);
    TEST_ASSERT_EQUAL_INT(1,item);
    Queue_Remove(buffer,&item);
    TEST_ASSERT_EQUAL_INT(2,item);
    Queue_Remove(buffer,&item);
    TEST_ASSERT_EQUAL_INT(3,item);
}
