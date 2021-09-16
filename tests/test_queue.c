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

    Queue_Init(&buffer, 4, NULL);
    
    // First burst:
    TEST_ASSERT_EQUAL_INT(QUEUE_OK ,Queue_Add(buffer, 1));
    TEST_ASSERT_EQUAL_INT(QUEUE_OK ,Queue_Add(buffer, 2));
    TEST_ASSERT_EQUAL_INT(QUEUE_OK ,Queue_Add(buffer, 3));

    TEST_ASSERT_EQUAL_INT(QUEUE_OK ,Queue_Remove(buffer,&item));
    TEST_ASSERT_EQUAL_INT(1,item);
    TEST_ASSERT_EQUAL_INT(QUEUE_OK ,Queue_Remove(buffer,&item));
    TEST_ASSERT_EQUAL_INT(2,item);
    TEST_ASSERT_EQUAL_INT(QUEUE_OK ,Queue_Remove(buffer,&item));
    TEST_ASSERT_EQUAL_INT(3,item);

    // Second burst:
    TEST_ASSERT_EQUAL_INT(QUEUE_OK ,Queue_Add(buffer, 4));
    TEST_ASSERT_EQUAL_INT(QUEUE_OK ,Queue_Add(buffer, 5));
    TEST_ASSERT_EQUAL_INT(QUEUE_OK ,Queue_Add(buffer, 6));

    TEST_ASSERT_EQUAL_INT(QUEUE_OK ,Queue_Remove(buffer,&item));
    TEST_ASSERT_EQUAL_INT(4,item);
    TEST_ASSERT_EQUAL_INT(QUEUE_OK ,Queue_Remove(buffer,&item));
    TEST_ASSERT_EQUAL_INT(5,item);
    TEST_ASSERT_EQUAL_INT(QUEUE_OK ,Queue_Remove(buffer,&item));
    TEST_ASSERT_EQUAL_INT(6,item);
}

TEST(queue, AddBeyondLimits)
{
    int tmp;
    Queue_Init(&buffer, 5, NULL);

    TEST_ASSERT_EQUAL_INT(QUEUE_OK,   Queue_Add(buffer, 1));
    TEST_ASSERT_EQUAL_INT(QUEUE_OK,   Queue_Add(buffer, 1));
    TEST_ASSERT_EQUAL_INT(QUEUE_OK,   Queue_Remove(buffer, &tmp));
    TEST_ASSERT_EQUAL_INT(QUEUE_OK,   Queue_Add(buffer, 1));
    TEST_ASSERT_EQUAL_INT(QUEUE_OK,   Queue_Add(buffer, 1));
    TEST_ASSERT_EQUAL_INT(QUEUE_OK,   Queue_Add(buffer, 1));
    TEST_ASSERT_EQUAL_INT(QUEUE_OK,   Queue_Add(buffer, 1));
    TEST_ASSERT_EQUAL_INT(QUEUE_FULL, Queue_Add(buffer, 1));
}

TEST(queue, RemoveBeyondLimits)
{
    int item;

    Queue_Init(&buffer, 5, NULL);

    TEST_ASSERT_EQUAL_INT(QUEUE_EMPTY, Queue_Peek(buffer, &item));
    TEST_ASSERT_EQUAL_INT(QUEUE_OK,    Queue_Add(buffer, 1));
    TEST_ASSERT_EQUAL_INT(QUEUE_OK,    Queue_Remove(buffer, &item));
    TEST_ASSERT_EQUAL_INT(QUEUE_EMPTY, Queue_Remove(buffer, &item));
}

TEST(queue, QueuePeek)
{
    int item;
    Queue_Init(&buffer, 10, NULL);

    Queue_Add(buffer, 55);
    Queue_Peek(buffer, &item);
    TEST_ASSERT_EQUAL_INT(55, item);
    Queue_Remove(buffer, &item);
    TEST_ASSERT_EQUAL_INT(55, item);
}

TEST(queue, QueueSize)
{
    Queue_Init(&buffer, 10, NULL);

    Queue_Add(buffer, 1);
    Queue_Add(buffer, 1);
    Queue_Add(buffer, 1);
    Queue_Add(buffer, 1);
    Queue_Add(buffer, 1);
    Queue_Add(buffer, 1);
    Queue_Add(buffer, 1);

    TEST_ASSERT_EQUAL_INT(7, Queue_Size(buffer));
}