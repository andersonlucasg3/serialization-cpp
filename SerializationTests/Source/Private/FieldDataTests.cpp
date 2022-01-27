#include "FieldDataTests.h"

#include <cstring>

#include "Test.h"
#include "FieldData.h"

void ImplFieldDataTests::TestFieldData()
{
    FieldData<int> fieldData = FieldData<int>("value");
    fieldData.SetValue(10);

    Test::AreEqual(10, fieldData.GetValue());
    
    fieldData.SetValue(20);
    
    Test::AreEqual(20, fieldData.GetValue());
    
    Test::AreEqual("value", fieldData.GetName());
}

template<typename TType>
void TestDataType(TType value)
{
    FieldData<TType> fieldData = FieldData<TType>("value");
    fieldData.SetValue(value);
    Test::AreEqual(value, fieldData.GetValue());
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
    
    Test::AreEqual(str, fieldData.GetValue());
    Test::AreEqual(sizeof(uint32_t) + strlen(str), fieldData.GetSize());
    
    str = "B string with B value";
    
    
    Test::AreNotEqual(str, fieldData.GetValue());
    Test::AreEqual(sizeof(uint32_t) + strlen(str), fieldData.GetSize());
    
    str = "Little string";
    
    Test::AreNotEqual(str, fieldData.GetValue());
    Test::AreNotEqual(sizeof(uint32_t) + strlen(str), fieldData.GetSize());
}
