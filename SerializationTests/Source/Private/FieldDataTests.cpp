#include "FieldDataTests.h"
#include "FieldData.h"

void ImplFieldDataTests::TestFieldData()
{
    int value;
    FieldData<int> fieldData = FieldData<int>(&value, "value");
    
    value = 10;
    
    Assert::AreEqual(value, fieldData.GetValue());
    
    fieldData.SetValue(20);
    
    Assert::AreEqual(value, fieldData.GetValue());
    
    Assert::AreEqual("value", fieldData.GetName());
}
