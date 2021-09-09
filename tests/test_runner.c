/*
 *
 */

#include "unity_fixture.h"

TEST_GROUP_RUNNER(stack)
{
    RUN_TEST_CASE(stack, InitializeStackDynamically);
    RUN_TEST_CASE(stack, InitializeStackDynamicallyWrong);
    //RUN_TEST_CASE(stack, InitializeStackStatically);
    //RUN_TEST_CASE(stack, InitializeStackStaticallyWrong);
    RUN_TEST_CASE(stack, PushPopStackDynamically);
    //RUN_TEST_CASE(stack, PushPopStackStatically);
    RUN_TEST_CASE(stack, PushBeyondLimits);
    RUN_TEST_CASE(stack, StackPeek);
    RUN_TEST_CASE(stack, SizeOfStack);
}

static void RunAllTests(void)
{
    RUN_TEST_GROUP(stack);
}

int main(int argc, char * argv[])
{
    return UnityMain(argc, argv, RunAllTests);
}
