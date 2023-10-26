#include <unity.h>
#include "calculateTimings.h"
#include "BitVector.h"
#include "constants.h"

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void testCalculateTiming()
{
    bool testArray[] = {true, true, true, true, true, false, false, false, true, true, true, true, true, true, true, false, false, false, false, false, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, true, true, true, true, true, true, false, false, false, false, false, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, false, false, false, false, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true};

    BitVector<SIGNALBITVECTORSIZE> testBitvector;

    for (int i = 0; i < (int) (sizeof(testArray)/sizeof(testArray[0])); i++)
    {
        testBitvector[i] = testArray[i];
    }

    short result = calculateTimings(testBitvector);

    char resultString[50];
    snprintf(resultString, sizeof(resultString), "Result was: %d", result);
    TEST_MESSAGE(resultString);
    TEST_ASSERT_TRUE(result == 7);
}

void loop() {}

void setup() {
    delay(2000);
    UNITY_BEGIN();

    RUN_TEST(testCalculateTiming);

    UNITY_END();
}
