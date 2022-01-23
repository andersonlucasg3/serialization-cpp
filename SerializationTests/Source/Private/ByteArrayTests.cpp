#include "ByteArrayTests.h"

#include "Assert.h"
#include "ByteArray.h"
#include <stdint.h>

void ImplByteArrayTests::TestByteArray()
{
    uint8_t buffer1[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
    uint8_t buffer2[] = { 7, 6, 5, 4, 3, 2, 1, 0 };
    uint8_t* buffer3 = new uint8_t[8] { 5, 4, 3, 2, 1, 7, 6, 0 };
    
    ByteArray byteArray1;
    byteArray1.Set(buffer1, 8);
    
    ByteArray byteArray2(buffer2, 8);
    
    ByteArray byteArray3(buffer3, 8, false);
    
    Assert::AreNotEqual(buffer1, const_cast<uint8_t*>(byteArray1.GetBuffer()));
    Assert::AreNotEqual(buffer2, const_cast<uint8_t*>(byteArray2.GetBuffer()));
    Assert::AreEqual(buffer3, const_cast<uint8_t*>(byteArray3.GetBuffer()));
    
    byteArray1 = byteArray2;
    
    Assert::AreNotEqual(buffer1, const_cast<uint8_t*>(byteArray1.GetBuffer()));
    Assert::AreNotEqual(buffer2, const_cast<uint8_t*>(byteArray2.GetBuffer()));
    Assert::AreEqual(const_cast<uint8_t*>(byteArray1.GetBuffer()), const_cast<uint8_t*>(byteArray2.GetBuffer()));
    
    ByteArray byteArray4 = byteArray3;
    
    Assert::AreEqual(buffer3, const_cast<uint8_t*>(byteArray4.GetBuffer()));
}
