/*
 *
 */

#include "unity_fixture.h"

TEST_GROUP_RUNNER(lifo)
{
    RUN_TEST_CASE(lifo, InitializationTest);
}

static void RunAllTests(void)
{
    RUN_TEST_GROUP(lifo);
}

int main(int argc, char * argv[])
{
    return UnityMain(argc, argv, RunAllTests);
}
