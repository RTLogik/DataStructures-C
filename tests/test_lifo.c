/*
    Pushear beyond limits(8/16/32)
    Popear beyond limits
 */

#include "unity_fixture.h"
#include "lifo.h"

TEST_GROUP(lifo);

TEST_SETUP(lifo)
{
    
}

TEST_TEAR_DOWN(lifo)
{
    
}

TEST(lifo, InitializeLIFOinHeap)
{
    LIFO_t lbuf;
    LIFO_Status status = LIFO_Init(lbuf, 20);
    TEST_ASSERT_EQUAL_INT(0,status);
}


TEST(lifo, InitializeLIFOinHeapWrong)
{
    int lbuf;
    LIFO_Status status = LIFO_Init(lbuf, 20);
    TEST_ASSERT_EQUAL_INT(0,status);
}

// TEST(lifo, InitializeLIFOinStack)
// {
//     int buffer[20];
//     LIFO_t lbuf;
//     lbuf->base = buffer;
//     LIFO_Status status = LIFO_Init(&lbuf);
//     TEST_ASSERT_EQUAL_INT(0,status);
// }

// TEST(lifo, InitializeLIFOinStackWrong)
// {
//     LIFO_t lbuf;
//     lbuf.length = 5;
//     lbuf.width  = 7;
//     LIFO_Status status = LIFO_Init(&lbuf);
//     TEST_ASSERT_EQUAL_INT(1,status);
// }

TEST(lifo, PushPopLIFOinHeap)
{
    int popItem;
    LIFO_t lbuf;
    LIFO_Init(lbuf, 20);

    LIFO_Push(lbuf, 24);
    LIFO_Push(lbuf, 8);
    LIFO_Push(lbuf, 88);
    LIFO_Pop(lbuf,&popItem);
    TEST_ASSERT_EQUAL_INT(88,popItem);
    LIFO_Pop(lbuf,&popItem);
    TEST_ASSERT_EQUAL_INT(8,popItem);
    LIFO_Pop(lbuf,&popItem);
    TEST_ASSERT_EQUAL_INT(24,popItem);
}

// TEST(lifo, PushPopLIFOinStack)
// {
//     uint32_t popItem;
//     LIFO_t lbuf;
//     lbuf.length = 5;
//     lbuf.width  = 4;
//     LIFO_Init(&lbuf);
//     LIFO_Push(&lbuf, 24);
//     LIFO_Push(&lbuf, 8);
//     LIFO_Push(&lbuf, 88);
//     LIFO_Pop(&lbuf,&popItem);
//     TEST_ASSERT_EQUAL_INT32(88,popItem);
//     LIFO_Pop(&lbuf,&popItem);
//     TEST_ASSERT_EQUAL_INT32(8,popItem);
//     LIFO_Pop(&lbuf,&popItem);
//     TEST_ASSERT_EQUAL_INT32(24,popItem);
// }

TEST(lifo, PushBeyondLimits)
{
    LIFO_t lbuf;
    LIFO_Init(lbuf, 5);

    for(int i = 0; i < 5; i++) {
        if (LIFO_Push(lbuf, 10) == LIFO_FULL) {
            char str[30];
            sprintf(str, "Full before time, length=%d",i);
            TEST_FAIL_MESSAGE(str);
        }
    }
    
    LIFO_Status status = LIFO_Push(lbuf, 4);
    TEST_ASSERT_EQUAL_INT(LIFO_FULL, status);
}