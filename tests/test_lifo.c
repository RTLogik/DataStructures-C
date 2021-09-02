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
    LIFO_t *lbuf  = malloc(sizeof(LIFO_t));
    LIFO_t *lbuf2 = malloc(sizeof(LIFO_t));
    LIFO_t *lbuf4 = malloc(sizeof(LIFO_t));
    lbuf->length = 5;
    lbuf->width  = 1;
    lbuf2->length = 5;
    lbuf2->width  = 2;
    lbuf4->length = 5;
    lbuf4->width  = 4;
    LIFO_Status status;
    status = LIFO_Init(lbuf);
    TEST_ASSERT_EQUAL_INT(0,status);
    status = LIFO_Init(lbuf2);
    TEST_ASSERT_EQUAL_INT(0,status);
    status = LIFO_Init(lbuf4);
    TEST_ASSERT_EQUAL_INT(0,status);
}


TEST(lifo, InitializeLIFOinHeapWrong)
{
    LIFO_t *lbuf = malloc(sizeof(LIFO_t));
    lbuf->length = 5;
    lbuf->width  = 7;
    LIFO_Status status = LIFO_Init(lbuf);
    TEST_ASSERT_EQUAL_INT(1,status);
}

TEST(lifo, InitializeLIFOinStack)
{
    LIFO_t lbuf;
    lbuf.length = 5;
    lbuf.width  = 1;
    LIFO_Status status = LIFO_Init(&lbuf);
    TEST_ASSERT_EQUAL_INT(0,status);
}

TEST(lifo, InitializeLIFOinStackWrong)
{
    LIFO_t lbuf;
    lbuf.length = 5;
    lbuf.width  = 7;
    LIFO_Status status = LIFO_Init(&lbuf);
    TEST_ASSERT_EQUAL_INT(1,status);
}

TEST(lifo, PushPopLIFOinHeap8)
{
    uint8_t popItem;
    LIFO_t *lbuf = malloc(sizeof(LIFO_t));
    lbuf->length = 5;
    lbuf->width  = 1;
    LIFO_Init(lbuf);
    LIFO_Push(lbuf, 13);
    LIFO_Push(lbuf, 8);
    LIFO_Pop(lbuf,&popItem);
    TEST_ASSERT_EQUAL_INT8(8,popItem);
    LIFO_Pop(lbuf,&popItem);
    TEST_ASSERT_EQUAL_INT8(13,popItem);
}

TEST(lifo, PushPopLIFOinHeap16)
{
    uint16_t popItem;
    LIFO_t *lbuf = malloc(sizeof(LIFO_t));
    lbuf->length = 5;
    lbuf->width  = 2;
    LIFO_Init(lbuf);
    LIFO_Push(lbuf, 13);
    LIFO_Push(lbuf, 8);
    LIFO_Pop(lbuf,&popItem);
    TEST_ASSERT_EQUAL_INT16(8,popItem);
    LIFO_Pop(lbuf,&popItem);
    TEST_ASSERT_EQUAL_INT16(13,popItem);
}

TEST(lifo, PushPopLIFOinHeap32)
{
    uint32_t popItem;
    LIFO_t *lbuf = malloc(sizeof(LIFO_t));
    lbuf->length = 5;
    lbuf->width  = 4;
    LIFO_Init(lbuf);
    LIFO_Push(lbuf, 24);
    LIFO_Push(lbuf, 8);
    LIFO_Push(lbuf, 88);
    LIFO_Pop(lbuf,&popItem);
    TEST_ASSERT_EQUAL_INT32(88,popItem);
    LIFO_Pop(lbuf,&popItem);
    TEST_ASSERT_EQUAL_INT32(8,popItem);
    LIFO_Pop(lbuf,&popItem);
    TEST_ASSERT_EQUAL_INT32(24,popItem);
}

TEST(lifo, PushPopLIFOinStack32)
{
    uint32_t popItem;
    LIFO_t lbuf;
    lbuf.length = 5;
    lbuf.width  = 4;
    LIFO_Init(&lbuf);
    LIFO_Push(&lbuf, 24);
    LIFO_Push(&lbuf, 8);
    LIFO_Push(&lbuf, 88);
    LIFO_Pop(&lbuf,&popItem);
    TEST_ASSERT_EQUAL_INT32(88,popItem);
    LIFO_Pop(&lbuf,&popItem);
    TEST_ASSERT_EQUAL_INT32(8,popItem);
    LIFO_Pop(&lbuf,&popItem);
    TEST_ASSERT_EQUAL_INT32(24,popItem);
}

TEST(lifo, PushBeyondLimits8)
{
    LIFO_t *lbuf = malloc(sizeof(LIFO_t));
    lbuf->width = 1;
    lbuf->length = 3;
    LIFO_Init(lbuf);

    for(int i = 0; i < 4; i++) {
        if (LIFO_Push(lbuf, (uint8_t)4) == LIFO_FULL) {
            char str[30];
            sprintf(str, "Full before time, length=%d",i);
            TEST_FAIL_MESSAGE(str);
        }
    }
    
    LIFO_Status status = LIFO_Push(lbuf, (uint8_t)4);
    TEST_ASSERT_EQUAL_INT(LIFO_FULL, status);

}