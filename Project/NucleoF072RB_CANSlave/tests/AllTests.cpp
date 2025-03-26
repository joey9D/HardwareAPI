#include "CppUTest/CommandLineTestRunner.h"

TEST_GROUP(ExampleGroup)
{
};

TEST(ExampleGroup, Test1)
{
    CHECK_EQUAL(1, 1);
}

int main(int argc, char** argv)
{
    return CommandLineTestRunner::RunAllTests(argc, argv);
}