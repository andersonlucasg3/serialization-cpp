#if defined(__APPLE__)

#import <XCTest/XCTest.h>

#import "Implementations/TestsImplementations.h"

#define DECLARE_TEST(className, testName) \
- (void) testName \
{ \
    className :: testName (); \
}

@interface SerializationTests : XCTestCase

@end

@implementation SerializationTests

DECLARE_TEST(TestsImplementations, TestFieldData)

DECLARE_TEST(TestsImplementations, TestSerializable)

DECLARE_TEST(TestsImplementations, TestSerializableOrder)

DECLARE_TEST(TestsImplementations, TestSerializeStruct)

@end

#endif
