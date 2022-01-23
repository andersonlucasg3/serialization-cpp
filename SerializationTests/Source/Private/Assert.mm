#include "Assert.h"
#include "ByteArray.h"

#import <XCTest/XCTest.h>

template<typename TType>
void Assert::AreEqual(TType value1, TType value2)
{
    if constexpr (std::is_same_v<TType, const char*>)
    {
        NSString* string1 = [[NSString alloc] initWithUTF8String:value1];
        NSString* string2 = [[NSString alloc] initWithUTF8String:value2];
        XCTAssertTrue([string1 isEqualToString:string2], @"\"%@\" is not equal to \"%@\"", string1, string2);
        return;
    }
    else if constexpr (std::is_same_v<TType, ByteArray>)
    {
        XCTAssertTrue(value1 == value2,
                      @"byte array value1 %s with length %zu is not equal to byte array value2 %s with length %zu",
                      value1.GetBuffer(), value1.Length(),
                      value2.GetBuffer(), value2.Length());
        return;
    }
    else
    {
        XCTAssertEqual(value1, value2);
    }
}

template<typename TType>
void Assert::AreNotEqual(TType value1, TType value2)
{
    if constexpr (std::is_same_v<TType, const char*>)
    {
        NSString* string1 = [[NSString alloc] initWithUTF8String:value1];
        NSString* string2 = [[NSString alloc] initWithUTF8String:value2];
        XCTAssertFalse([string1 isEqualToString:string2], @"\"%@\" is equal to \"%@\"", string1, string2);
        return;
    }
    
    XCTAssertNotEqual(value1, value2);
}

#define INSTANTIATE_ALL(type) \
template void Assert::AreEqual(type, type); \
template void Assert::AreNotEqual(type, type); \
template void Assert::AreEqual(type*, type*); \
template void Assert::AreNotEqual(type*, type*);

#include "TemplateInstantiation.hpp"
