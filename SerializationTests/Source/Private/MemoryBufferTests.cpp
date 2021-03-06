#include "MemoryBufferTests.h"

#include <cstdint>

#include "Test.h"
#include "MemoryBuffer.h"

void ImplMemoryBufferTests::TestMemoryBuffer()
{
    uint8_t buffer1[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
    uint8_t buffer2[] = { 7, 6, 5, 4, 3, 2, 1, 0 };
    uint8_t* buffer3 = new uint8_t[8] { 5, 4, 3, 2, 1, 7, 6, 0 };
    
    MemoryBuffer<uint8_t> byteArray1;
    byteArray1.Set(buffer1, 8);
    
    MemoryBuffer<uint8_t> byteArray2(buffer2, 8);
    
    MemoryBuffer<uint8_t> byteArray3(buffer3, 8, false);
    
    Test::AreNotEqual(buffer1, const_cast<uint8_t*>(byteArray1.GetBuffer()));
    Test::AreNotEqual(buffer2, const_cast<uint8_t*>(byteArray2.GetBuffer()));
    Test::AreEqual(buffer3, const_cast<uint8_t*>(byteArray3.GetBuffer()));
    
    byteArray1 = byteArray2;

    Test::AreNotEqual(buffer1, const_cast<uint8_t*>(byteArray1.GetBuffer()));
    Test::AreNotEqual(buffer2, const_cast<uint8_t*>(byteArray2.GetBuffer()));
    Test::AreEqual(const_cast<uint8_t*>(byteArray1.GetBuffer()), const_cast<uint8_t*>(byteArray2.GetBuffer()));
    
    MemoryBuffer byteArray4 = byteArray3;

    Test::AreEqual(buffer3, const_cast<uint8_t*>(byteArray4.GetBuffer()));
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
    
    Test::AreNotEqual(stackBuffer, const_cast<uint8_t*>(stackCopy.GetBuffer()));
    Test::AreEqual(heapBuffer1, const_cast<uint8_t*>(heapCopy1.GetBuffer()));
    Test::AreNotEqual(heapBuffer2, const_cast<uint8_t*>(heapCopy2.GetBuffer()));
    
    delete[] heapBuffer2;
}

void ImplMemoryBufferTests::TestMemoryBufferTypes()
{
    MemoryBuffer<uint16_t> uint16Buffer(new uint16_t[2] { 14, 152 }, 2, false);
    
    Test::AreEqual<size_t>(2, uint16Buffer.Length());
    Test::AreEqual<size_t>(4, uint16Buffer.Length<uint8_t>());
    
    MemoryBuffer<uint64_t> uint64Buffer(new uint64_t[2]{ 1512, 9395 }, 2, false);
    
    Test::AreEqual<size_t>(2, uint64Buffer.Length());
    Test::AreEqual<size_t>(4, uint64Buffer.Length<uint32_t>());
    Test::AreEqual<size_t>(8, uint64Buffer.Length<uint16_t>());
    Test::AreEqual<size_t>(16, uint64Buffer.Length<uint8_t>());
    
    MemoryBuffer<float> floatBuffer(new float[2]{ 515.124, 3.14 }, 2, false);
    
    Test::AreEqual<size_t>(2, floatBuffer.Length());
    Test::AreEqual<size_t>(8, floatBuffer.Length<uint8_t>());
    
    MemoryBuffer<double> doubleBuffer(new double[2]{ 19835.931859583958, 135.19385399835 }, 2, false);
    
    Test::AreEqual<size_t>(2, doubleBuffer.Length());
    Test::AreEqual<size_t>(16, doubleBuffer.Length<uint8_t>());
}
