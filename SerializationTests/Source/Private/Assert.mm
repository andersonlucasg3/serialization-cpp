#include "Assert.h"

#import <XCTest/XCTest.h>

template<typename TType>
void Assert::AreEqual(TType value1, TType value2)
{
    if constexpr (std::is_same_v<TType, const char*>)
    {
        NSString* string1 = [[NSString alloc] initWithUTF8String:value1];
        NSString* string2 = [[NSString alloc] initWithUTF8String:value2];
        XCTAssertEqual(string1, string2);
        return;
    }
    
    XCTAssertEqual(value1, value2);
}

#define INSTANTIATE_ALL(type) \
template void Assert::AreEqual(type, type);

#include "TemplateInstantiation.hpp"
