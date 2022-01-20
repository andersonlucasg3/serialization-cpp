#pragma once

class TestsImplementations
{
public:
    static void TestFieldData();
    static void TestSerializable();
    static void TestSerializableOrder();
    static void TestSerializeStruct();
    static void TestDeserializeStruct();
    static void TestCopyingStructValue();
};

#define DECLARE_ALL_TESTS() \
    DECLARE_TEST(TestsImplementations, TestFieldData) \
    DECLARE_TEST(TestsImplementations, TestSerializable) \
    DECLARE_TEST(TestsImplementations, TestSerializableOrder) \
    DECLARE_TEST(TestsImplementations, TestSerializeStruct) \
    DECLARE_TEST(TestsImplementations, TestDeserializeStruct) \
    DECLARE_TEST(TestsImplementations, TestCopyingStructValue)

#if !defined(__APPLE__)

#define DECLARE_TEST_CLASS() \
namespace SerializationTests \
{ \
    TEST_CLASS(SerializationTests) \
    { \
    public: \
        DECLARE_ALL_TESTS() \
    }; \
}

#define DECLARE_TEST(className, funcName) \
TEST_METHOD(funcName) { className :: funcName (); }

#else

#define DECLARE_TEST_CLASS() \
@interface SerializationTests : XCTestCase @end \
@implementation SerializationTests \
DECLARE_ALL_TESTS() \
@end

#define DECLARE_TEST(className, funcName) \
- (void) test##funcName { className :: funcName (); }

#endif
