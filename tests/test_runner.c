/*
 *
 */

#include "unity_fixture.h"

TEST_GROUP_RUNNER(lifo)
{
    RUN_TEST_CASE(lifo, InitializeLIFOinHeap);
    RUN_TEST_CASE(lifo, InitializeLIFOinHeapWrong);
    RUN_TEST_CASE(lifo, InitializeLIFOinStack);
    RUN_TEST_CASE(lifo, InitializeLIFOinStackWrong);
    RUN_TEST_CASE(lifo, PushPopLIFOinHeap8);
    RUN_TEST_CASE(lifo, PushPopLIFOinHeap16);
    RUN_TEST_CASE(lifo, PushPopLIFOinHeap32);
    RUN_TEST_CASE(lifo, PushPopLIFOinStack32);
    RUN_TEST_CASE(lifo, PushBeyondLimits8);
}

static void RunAllTests(void)
{
    RUN_TEST_GROUP(lifo);
}

int main(int argc, char * argv[])
{
    return UnityMain(argc, argv, RunAllTests);
}
