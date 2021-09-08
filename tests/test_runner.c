/*
 *
 */

#include "unity_fixture.h"

TEST_GROUP_RUNNER(lifo)
{
    RUN_TEST_CASE(lifo, InitializeLIFOinHeap);
    RUN_TEST_CASE(lifo, InitializeLIFOinHeapWrong);
    //RUN_TEST_CASE(lifo, InitializeLIFOinStack);
    //RUN_TEST_CASE(lifo, InitializeLIFOinStackWrong);
    RUN_TEST_CASE(lifo, PushPopLIFOinHeap);
    //RUN_TEST_CASE(lifo, PushPopLIFOinStack);
    RUN_TEST_CASE(lifo, PushBeyondLimits);
}

static void RunAllTests(void)
{
    RUN_TEST_GROUP(lifo);
}

int main(int argc, char * argv[])
{
    return UnityMain(argc, argv, RunAllTests);
}
