#pragma once

class ImplByteArrayTests
{
public:
    static void TestByteArray();
};

#define DECLARE_BYTE_ARRAY_TESTS() \
DECLARE_TEST(ByteArrayTests, TestByteArray)
