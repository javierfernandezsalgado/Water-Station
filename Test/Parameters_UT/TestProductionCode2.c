#include "ProductionCode2.h"
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(Event);

/* These should be ignored because they are commented out in various ways:
#include "whatever.h"
*/
//#include "somethingelse.h"

TEST_SETUP(Event)
{
}

TEST_TEAR_DOWN(Event)
{
}

TEST(Event, IgnoredTest)
{
    TEST_IGNORE_MESSAGE("This Test Was Ignored On Purpose");
}

TEST(Event, AnotherIgnoredTest)
{
    TEST_IGNORE_MESSAGE("These Can Be Useful For Leaving Yourself Notes On What You Need To Do Yet");
}

TEST(Event, ThisFunctionHasNotBeenTested_NeedsToBeImplemented)
{
    TEST_IGNORE(); //Like This
}
