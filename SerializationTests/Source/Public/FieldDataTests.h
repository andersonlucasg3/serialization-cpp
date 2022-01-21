#pragma once

#include "TestsMacros.h"

class ImplFieldDataTests {
public:
    static void TestFieldData();
    static void TestFieldDataTypes();
    static void TestFieldDataString();
};

#define DECLARE_TEST_FUNC(testFunc) DECLARE_TEST(FieldDataTests, testFunc)

#define DECLARE_FIELD_DATA_TESTS() \
DECLARE_TEST_FUNC(TestFieldData) \
DECLARE_TEST_FUNC(TestFieldDataTypes) \
DECLARE_TEST_FUNC(TestFieldDataString)
