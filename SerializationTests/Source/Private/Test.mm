#include <XCTest/XCTest.h>

#include "Test.h"

#include "MemoryBuffer.h"

#define DECLARE_ARE_EQUAL_SIG(type) \
void CheckAreEqual(type value1, type value2)

#define DECLARE_ARE_NOT_EQUAL_SIG(type) \
void CheckAreNotEqual(type value1, type value2)

#define DECLARE_ARE_EQUAL_STRING(type) \
DECLARE_ARE_EQUAL_SIG(type) \
{ \
    NSString* string1 = [[NSString alloc] initWithUTF8String:value1]; \
    NSString* string2 = [[NSString alloc] initWithUTF8String:value2]; \
    XCTAssertTrue([string1 isEqualToString:string2], @"\"%@\" is not equal to \"%@\"", string1, string2); \
}

#define DECLARE_ARE_NOT_EQUAL_STRING(type) \
DECLARE_ARE_NOT_EQUAL_SIG(type) \
{ \
    NSString* string1 = [[NSString alloc] initWithUTF8String:value1]; \
    NSString* string2 = [[NSString alloc] initWithUTF8String:value2]; \
    XCTAssertFalse([string1 isEqualToString:string2], @"\"%@\" is equal to \"%@\"", string1, string2); \
}

#define DECLARE_IS_TRUE(type) \
DECLARE_IS_TRUE_SIG(type) \
{ \
    XCTAssertTrue(isTrue, message); \
}

#define DECLARE_ARE_EQUAL_ANY(type) \
DECLARE_ARE_EQUAL_SIG(type) \
{ \
    XCTAssertEqual(value1, value2); \
}

#define DECLARE_ARE_NOT_EQUAL_ANY(type) \
DECLARE_ARE_NOT_EQUAL_SIG(type) \
{ \
    XCTAssertNotEqual(value1, value2); \
}

#define DECLARE_ALL_IMPL_STRING(type) \
DECLARE_ARE_EQUAL_STRING(type) \
DECLARE_ARE_NOT_EQUAL_STRING(type)

#define DECLARE_ALL_IMPL(type) \
DECLARE_ARE_EQUAL_ANY(type) \
DECLARE_ARE_NOT_EQUAL_ANY(type)

DECLARE_ALL_IMPL_STRING(const char*)
DECLARE_ALL_IMPL(uint8_t)
DECLARE_ALL_IMPL(int8_t)
DECLARE_ALL_IMPL(uint16_t)
DECLARE_ALL_IMPL(int16_t)
DECLARE_ALL_IMPL(uint32_t)
DECLARE_ALL_IMPL(int32_t)
DECLARE_ALL_IMPL(uint64_t)
DECLARE_ALL_IMPL(int64_t)
DECLARE_ALL_IMPL(size_t)
DECLARE_ALL_IMPL(float)
DECLARE_ALL_IMPL(double)
DECLARE_ALL_IMPL(uint8_t*)

DECLARE_ARE_EQUAL_SIG(std::string)
{
    CheckAreEqual(value1.c_str(), value2.c_str());
}

DECLARE_ARE_NOT_EQUAL_SIG(std::string)
{
    CheckAreNotEqual(value1.c_str(), value2.c_str());
}

void CheckIsTrue(bool isTrue, const char* message)
{
    if (message != nullptr && strlen(message) > 0)
    {
        NSString* string = [[NSString alloc] initWithUTF8String:message];
        XCTAssertTrue(isTrue, @"%@", string);
        
        return;
    }
    
    XCTAssertTrue(isTrue);
}

void Test::IsTrue(bool isTrue)
{
    CheckIsTrue(isTrue, nullptr);
}
