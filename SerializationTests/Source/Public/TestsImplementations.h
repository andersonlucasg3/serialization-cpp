#pragma once

#include "Serializable.h"

struct Model : public Serializable
{
public:
    DECLARE_VAR(int, a)
    DECLARE_VAR(int, b)
    DECLARE_VAR(float, c)
};

class TestsImplementations
{
public:
    static void TestFieldData();
    static void TestSerializable();
    static void TestSerializableOrder();
    static void TestSerializeStruct();
};

#if !defined(__APPLE__)
#define DECLARE_TEST(className, funcName) \
TEST_METHOD(funcName) { className :: funcName (); }
#else
#define DECLARE_TEST(className, funcName) \
- (void) test##funcName { className::funcName (); }
#endif


#define DECLARE_ALL_TESTS() \
DECLARE_TEST(TestsImplementations, TestFieldData) \
DECLARE_TEST(TestsImplementations, TestSerializable) \
DECLARE_TEST(TestsImplementations, TestSerializableOrder) \
DECLARE_TEST(TestsImplementations, TestSerializeStruct)