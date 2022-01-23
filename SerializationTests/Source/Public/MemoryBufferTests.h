#pragma once

class ImplMemoryBufferTests
{
public:
    static void TestMemoryBuffer();
    static void TestMemoryBufferAllocation();
};

#define DECLARE_MEMORY_BUFFER_TESTS() \
DECLARE_TEST(MemoryBufferTests, TestMemoryBuffer) \
DECLARE_TEST(MemoryBufferTests, TestMemoryBufferAllocation)
