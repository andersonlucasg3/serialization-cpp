#pragma once

#if !defined(__APPLE__)

#define DECLARE_TEST_CLASS(className, declareTests) \
namespace SerializationTests \
{ \
    TEST_CLASS(className) \
    { \
    public: \
        declareTests \
    }; \
}

#define DECLARE_TEST(className, funcName) \
TEST_METHOD(funcName) { Impl##className :: funcName (); }

#else

#define DECLARE_TEST_CLASS(className, declareTests) \
@interface className : XCTestCase @end \
@implementation className \
declareTests \
@end

#define DECLARE_TEST(className, funcName) \
- (void) test##funcName { Impl##className :: funcName (); }

#endif
