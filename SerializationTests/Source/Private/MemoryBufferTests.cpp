#include "MemoryBufferTests.h"

#include "Assert.h"
#include "MemoryBuffer.h"
#include <stdint.h>

void ImplMemoryBufferTests::TestMemoryBuffer()
{
    uint8_t buffer1[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
    uint8_t buffer2[] = { 7, 6, 5, 4, 3, 2, 1, 0 };
    uint8_t* buffer3 = new uint8_t[8] { 5, 4, 3, 2, 1, 7, 6, 0 };
    
    MemoryBuffer<uint8_t> byteArray1;
    byteArray1.Set(buffer1, 8);
    
    MemoryBuffer<uint8_t> byteArray2(buffer2, 8);
    
    MemoryBuffer<uint8_t> byteArray3(buffer3, 8, false);
    
    Assert::AreNotEqual(buffer1, const_cast<uint8_t*>(byteArray1.GetBuffer()));
    Assert::AreNotEqual(buffer2, const_cast<uint8_t*>(byteArray2.GetBuffer()));
    Assert::AreEqual(buffer3, const_cast<uint8_t*>(byteArray3.GetBuffer()));
    
    byteArray1 = byteArray2;
    
    Assert::AreNotEqual(buffer1, const_cast<uint8_t*>(byteArray1.GetBuffer()));
    Assert::AreNotEqual(buffer2, const_cast<uint8_t*>(byteArray2.GetBuffer()));
    Assert::AreEqual(const_cast<uint8_t*>(byteArray1.GetBuffer()), const_cast<uint8_t*>(byteArray2.GetBuffer()));
    
    MemoryBuffer byteArray4 = byteArray3;
    
    Assert::AreEqual(buffer3, const_cast<uint8_t*>(byteArray4.GetBuffer()));
}

void ImplMemoryBufferTests::TestMemoryBufferAllocation()
{
    uint8_t stackBuffer[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
    uint8_t* heapBuffer1 = new uint8_t[8] { 0, 1, 2, 3, 4, 5, 6, 7 };
    uint8_t* heapBuffer2 = new uint8_t[8] { 0, 1, 2, 3, 4, 5, 6, 7 };
    
    MemoryBuffer byteArrayStack(stackBuffer, 8);
    MemoryBuffer byteArrayHeap1(heapBuffer1, 8, false);
    MemoryBuffer byteArrayHeap2(heapBuffer2, 8, true);
    
    MemoryBuffer stackCopy = byteArrayStack;
    MemoryBuffer heapCopy1 = byteArrayHeap1;
    MemoryBuffer heapCopy2 = byteArrayHeap2;
    
    Assert::AreNotEqual(stackBuffer, const_cast<uint8_t*>(stackCopy.GetBuffer()));
    Assert::AreEqual(heapBuffer1, const_cast<uint8_t*>(heapCopy1.GetBuffer()));
    Assert::AreNotEqual(heapBuffer2, const_cast<uint8_t*>(heapCopy2.GetBuffer()));
    
    delete[] heapBuffer2;
}
