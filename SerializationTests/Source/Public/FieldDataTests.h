#pragma once

#include "TestsMacros.h"

class ImplFieldDataTests {
public:
    static void TestFieldData();
};

#define DECLARE_FIELD_DATA_TESTS() \
DECLARE_TEST(FieldDataTests, TestFieldData)
