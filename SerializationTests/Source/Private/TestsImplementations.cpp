#include "TestsImplementations.h"
#include "Assert.h"

void TestsImplementations::TestFieldData()
{
    int value;
    FieldData<int> fieldData = FieldData<int>(&value, "value");
    
    value = 10;
    
    Assert::AreEqual(value, fieldData.GetValue());
    
    fieldData.SetValue(20);
    
    Assert::AreEqual(value, fieldData.GetValue());
    
    Assert::AreEqual("value", fieldData.GetName());
}

void TestsImplementations::TestSerializable()
{
    Model m = Model();
    Assert::AreEqual(3, (int)m.GetFields().size());
}

void TestsImplementations::TestSerializableOrder()
{
    Model m = Model();
    const list<BaseFieldData*>& fields = m.GetFields();
    list<BaseFieldData*>::const_iterator iterator = fields.begin();
    Assert::AreEqual("a", (*iterator)->As<int>().GetName());
    advance(iterator, 1);
    Assert::AreEqual("b", (*iterator)->As<int>().GetName());
    advance(iterator, 1);
    Assert::AreEqual("c", (*iterator)->As<float>().GetName());
}

void TestsImplementations::TestSerializeStruct()
{
    Model m = Model();
    
    uint8_t* serializedData = m.Serialize();
    
    // TODO(anderson): check the data;
}
