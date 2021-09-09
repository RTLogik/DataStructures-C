/*
 *
 */

#include "unity_fixture.h"

TEST_GROUP_RUNNER(stack)
{
    RUN_TEST_CASE(stack, InitializeStackInHeap);
    RUN_TEST_CASE(stack, InitializeStackInHeapWrong);
    //RUN_TEST_CASE(stack, InitializeStackInStack);
    //RUN_TEST_CASE(stack, InitializeStackInStackWrong);
    RUN_TEST_CASE(stack, PushPopStackInHeap);
    //RUN_TEST_CASE(stack, PushPopStackInStack);
    RUN_TEST_CASE(stack, PushBeyondLimits);
}

static void RunAllTests(void)
{
    RUN_TEST_GROUP(stack);
}

int main(int argc, char * argv[])
{
    return UnityMain(argc, argv, RunAllTests);
}
