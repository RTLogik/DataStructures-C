
#include "unity_fixture.h"
#include "stack.h"

TEST_GROUP(stack);

Stack_t buffer;

TEST_SETUP(stack)
{
    //Stack_Init(&buffer, 10, NULL);
}

TEST_TEAR_DOWN(stack)
{
    //Stack_Delete(buffer);
}

TEST(stack, InitializeStackDynamically)
{
    TEST_ASSERT_EQUAL_INT(STACK_OK, Stack_Init(&buffer, 20, NULL));
    Stack_Delete(buffer);
}


TEST(stack, InitializeStackDynamicallyWrong)
{
    TEST_ASSERT_EQUAL_INT(STACK_LENGTH_ERROR, 
                          Stack_Init(&buffer, MAX_STACK_SIZE+1, NULL));
}

TEST(stack, InitializeStackStatically)
{
    int mem[20];
    TEST_ASSERT_EQUAL_INT(STACK_OK, Stack_Init(&buffer, 20, mem));
    Stack_Delete(buffer);
}

TEST(stack, PushPopStackDynamically)
{
    int popItem;

    Stack_Init(&buffer, 10, NULL);

    Stack_Push(buffer, 1);
    Stack_Push(buffer, 2);
    Stack_Push(buffer, 3);

    Stack_Pop(buffer,&popItem);
    TEST_ASSERT_EQUAL_INT(3,popItem);
    Stack_Pop(buffer,&popItem);
    TEST_ASSERT_EQUAL_INT(2,popItem);
    Stack_Pop(buffer,&popItem);
    TEST_ASSERT_EQUAL_INT(1,popItem);
}

TEST(stack, PushPopStackStatically)
{
    int popItem;
    int mem[5];
    Stack_Init(&buffer, 5, mem);

    Stack_Push(buffer, 1);
    Stack_Push(buffer, 2);
    Stack_Push(buffer, 3);

    Stack_Pop(buffer,&popItem);
    TEST_ASSERT_EQUAL_INT(3,popItem);
    Stack_Pop(buffer,&popItem);
    TEST_ASSERT_EQUAL_INT(2,popItem);
    Stack_Pop(buffer,&popItem);
    TEST_ASSERT_EQUAL_INT(1,popItem);
}

TEST(stack, PushBeyondLimits)
{
    Stack_Init(&buffer, 10, NULL);

    for(int i = 0; i < 10; i++) {
        if (Stack_Push(buffer, 1) == STACK_FULL) {
            char str[30];
            sprintf(str, "Full before time, length=%d",i);
            TEST_FAIL_MESSAGE(str);
        }
    }
    
    StackStatus_e status = Stack_Push(buffer, 1);
    TEST_ASSERT_EQUAL_INT(STACK_FULL, status);
}

TEST(stack, PopBeyondLimits)
{
    Stack_Init(&buffer, 5, NULL);

    TEST_ASSERT_EQUAL_INT(STACK_EMPTY, Stack_Peek(buffer, NULL));
    TEST_ASSERT_EQUAL_INT(STACK_EMPTY, Stack_Pop(buffer, NULL));
}

TEST(stack, StackPeek)
{
    int peekItem, tmp;
    
    Stack_Init(&buffer, 5, NULL);

    Stack_Push(buffer, 8);
    Stack_Push(buffer, 88);

    Stack_Peek(buffer,&peekItem);
    TEST_ASSERT_EQUAL_INT(88,peekItem);
    Stack_Pop(buffer,&tmp);
    Stack_Peek(buffer,&peekItem);
    TEST_ASSERT_EQUAL_INT(8,peekItem);
    Stack_Pop(buffer,&tmp);
    TEST_ASSERT_EQUAL_INT(STACK_EMPTY, Stack_Peek(buffer,&peekItem));    
}

TEST(stack, StackSize)
{
    Stack_Init(&buffer, 10, NULL);

    TEST_ASSERT_EQUAL_INT(0, Stack_Size(buffer));  

    Stack_Push(buffer, 1);
    Stack_Push(buffer, 1);
    Stack_Push(buffer, 1);
    Stack_Push(buffer, 1);
    Stack_Push(buffer, 1);
    Stack_Push(buffer, 1);

    TEST_ASSERT_EQUAL_INT(6, Stack_Size(buffer));    
}