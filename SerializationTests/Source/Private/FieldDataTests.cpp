#include "FieldDataTests.h"
#include "FieldData.h"
#include "MemoryBuffer.h"

#include "Assert.h"

void ImplFieldDataTests::TestFieldData()
{
    FieldData<int> fieldData = FieldData<int>("value");
    fieldData.SetValue(10);
        
    Assert::AreEqual(10, fieldData.GetValue());
    
    fieldData.SetValue(20);
    
    Assert::AreEqual(20, fieldData.GetValue());
    
    Assert::AreEqual("value", fieldData.GetName());
}

template<typename TType>
void TestDataType(TType value)
{
    FieldData<TType> fieldData = FieldData<TType>("value");
    fieldData.SetValue(value);
    Assert::AreEqual(value, fieldData.GetValue());
}

void ImplFieldDataTests::TestFieldDataTypes()
{
    TestDataType<uint8_t>(10);
    TestDataType<int8_t>(10);
    TestDataType<uint16_t>(10);
    TestDataType<int16_t>(10);
    TestDataType<uint32_t>(10);
    TestDataType<int32_t>(10);
    TestDataType<uint64_t>(10);
    TestDataType<int64_t>(10);
    TestDataType<float>(10.0);
    TestDataType<double>(10.0);
    TestDataType<const char *>("some string to be tested");
    uint8_t array[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
    TestDataType<MemoryBuffer<uint8_t>>(MemoryBuffer(array, 8));
}

void ImplFieldDataTests::TestFieldDataString()
{
    const char* str = "A string with A value";
    
    FieldData<const char*> fieldData = FieldData<const char*>("str");
    fieldData.SetValue(str);
    
    Assert::AreEqual(str, fieldData.GetValue());
    Assert::AreEqual(sizeof(uint32_t) + strlen(str), fieldData.GetSize());
    
    str = "B string with B value";
    
    
    Assert::AreNotEqual(str, fieldData.GetValue());
    Assert::AreEqual(sizeof(uint32_t) + strlen(str), fieldData.GetSize());
    
    str = "Little string";
    
    Assert::AreNotEqual(str, fieldData.GetValue());
    Assert::AreNotEqual(sizeof(uint32_t) + strlen(str), fieldData.GetSize());
}
