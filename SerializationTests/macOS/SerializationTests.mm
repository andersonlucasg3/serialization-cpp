#if defined(__APPLE__)

#import <XCTest/XCTest.h>

#import "Implementations/TestsImplementations.h"

@interface SerializationTests : XCTestCase

@end

@implementation SerializationTests

- (void)testSerializable
{
    TestsImplementations::TestSerializable();
}

- (void)testSerializableOrder
{
    TestsImplementations::TestSerializableOrder();
}

@end

#endif
