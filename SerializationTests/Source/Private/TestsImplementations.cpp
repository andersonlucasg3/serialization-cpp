#include "TestsImplementations.h"

#include <cstring>

#include "Assert.h"
#include "Serializable.h"

struct Model : public Serializable
{
public:
    DECLARE_VAR(int, a)
    DECLARE_VAR(int, b)
    DECLARE_VAR(float, c)
};

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
    m.a = 0;
    m.b = 1;
    m.c = 3.14;
    
    uint8_t* serializedData = m.Serialize();

    int value = 0;
    float fvalue = 3.14;
    size_t position = 0;

    uint8_t* compare = new uint8_t[m.GetTotalSizeInBytes()];

    memcpy(compare, &value, sizeof(int));
    position += sizeof(int);

    value = 1;

    memcpy(compare + position, &value, sizeof(int));
    position += sizeof(int);

    memcpy(compare + position, &fvalue, sizeof(float));
    position += sizeof(float);

    Assert::AreEqual(position, m.GetTotalSizeInBytes());

    for (int index = 0; index < m.GetTotalSizeInBytes(); ++index)
    {
        Assert::AreEqual(*(compare + index), *(serializedData + index));
    }
    
    delete[] serializedData;
    delete[] compare;
}

void TestsImplementations::TestDeserializeStruct()
{
    Model m = Model();
    m.a = 10;
    m.b = 50;
    m.c = 3.14;
    
    uint8_t* serialized = m.Serialize();
    
    //m = Model();
    m.a = 0;
    m.b = 0;
    m.c = 0.0;
    
    m.Deserialize(serialized);
    
    Assert::AreEqual<int>(10, m.a);
    Assert::AreEqual<int>(50, m.b);
    Assert::AreEqual<float>(3.14, m.c);
}
