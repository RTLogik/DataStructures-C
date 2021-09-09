#include "unity_fixture.h"
#include "stack.h"

TEST_GROUP(stack);

TEST_SETUP(stack)
{
    
}

TEST_TEAR_DOWN(stack)
{
    
}

TEST(stack, InitializeStackInHeap)
{
    Stack_t buffer;
    StackStatus_e status = Stack_Init(buffer, 20);
    TEST_ASSERT_EQUAL_INT(0,status);
}


TEST(stack, InitializeStackInHeapWrong)
{
    int buffer;
    StackStatus_e status = Stack_Init(buffer, 20);
    TEST_ASSERT_EQUAL_INT(0,status);
}

// TEST(Stack, InitializeStackinStack)
// {
//     int buffer[20];
//     Stack_t buffer;
//     buffer->base = buffer;
//     StackStatus_e status = Stack_Init(&buffer);
//     TEST_ASSERT_EQUAL_INT(0,status);
// }

// TEST(Stack, InitializeStackinStackWrong)
// {
//     Stack_t buffer;
//     buffer.length = 5;
//     buffer.width  = 7;
//     StackStatus_e status = Stack_Init(&buffer);
//     TEST_ASSERT_EQUAL_INT(1,status);
// }

TEST(stack, PushPopStackInHeap)
{
    int popItem;
    Stack_t buffer;
    Stack_Init(buffer, 20);

    Stack_Push(buffer, 24);
    Stack_Push(buffer, 8);
    Stack_Push(buffer, 88);
    Stack_Pop(buffer,&popItem);
    TEST_ASSERT_EQUAL_INT(88,popItem);
    Stack_Pop(buffer,&popItem);
    TEST_ASSERT_EQUAL_INT(8,popItem);
    Stack_Pop(buffer,&popItem);
    TEST_ASSERT_EQUAL_INT(24,popItem);
}

// TEST(Stack, PushPopStackinStack)
// {
//     uint32_t popItem;
//     Stack_t buffer;
//     buffer.length = 5;
//     buffer.width  = 4;
//     Stack_Init(&buffer);
//     Stack_Push(&buffer, 24);
//     Stack_Push(&buffer, 8);
//     Stack_Push(&buffer, 88);
//     Stack_Pop(&buffer,&popItem);
//     TEST_ASSERT_EQUAL_INT32(88,popItem);
//     Stack_Pop(&buffer,&popItem);
//     TEST_ASSERT_EQUAL_INT32(8,popItem);
//     Stack_Pop(&buffer,&popItem);
//     TEST_ASSERT_EQUAL_INT32(24,popItem);
// }

TEST(stack, PushBeyondLimits)
{
    Stack_t buffer;
    Stack_Init(buffer, 5);

    for(int i = 0; i < 5; i++) {
        if (Stack_Push(buffer, 10) == STACK_FULL) {
            char str[30];
            sprintf(str, "Full before time, length=%d",i);
            TEST_FAIL_MESSAGE(str);
        }
    }
    
    StackStatus_e status = Stack_Push(buffer, 4);
    TEST_ASSERT_EQUAL_INT(STACK_FULL, status);
}