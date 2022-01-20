#include "SerializableTests.h"

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

void ImplSerializableTests::TestSerializable()
{
    Model m = Model();
    Assert::AreEqual(3, (int)m.GetFields().size());
}

void ImplSerializableTests::TestSerializableOrder()
{
    Model m = Model();
    const list<BaseFieldData*>& fields = m.GetFields();
    list<BaseFieldData*>::const_iterator iterator = fields.begin();
    Assert::AreEqual("a", FieldData<int>::From(*iterator)->GetName());
    advance(iterator, 1);
    Assert::AreEqual("b", FieldData<int>::From(*iterator)->GetName());
    advance(iterator, 1);
    Assert::AreEqual("c", FieldData<float>::From(*iterator)->GetName());
}

void TestSerializeStructSigned(int sign)
{
    Model m = Model();
    m.a = 0 * sign;
    m.b = 1 * sign;
    m.c = 3.14 * sign;
    
    uint8_t* serializedData = m.Serialize();

    int value = 0 * sign;
    float fvalue = 3.14 * sign;
    size_t position = 0;

    uint8_t* compare = new uint8_t[m.GetTotalSizeInBytes()];

    memcpy(compare, &value, sizeof(int));
    position += sizeof(int);

    value = 1 * sign;

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

void ImplSerializableTests::TestSerializeStruct()
{
    TestSerializeStructSigned(1);
    TestSerializeStructSigned(-1);
}

void TestDeserializeStructSigned(int sign)
{
    Model m;
    m.a = 10 * sign;
    m.b = 50 * sign;
    m.c = 3.14 * sign;
    
    uint8_t* serialized = m.Serialize();
    
    Model mm;
    
    mm.Deserialize(serialized);
    
    Assert::AreEqual<int>(10 * sign, mm.a);
    Assert::AreEqual<int>(50 * sign, mm.b);
    Assert::AreEqual<float>(3.14 * sign, mm.c);
}

void ImplSerializableTests::TestDeserializeStruct()
{
    TestDeserializeStructSigned(1);
    TestDeserializeStructSigned(-1);
}

void ImplSerializableTests::TestCopyingStructValue()
{
    Model m;
    m.a = 10;
    m.b = 50;
    m.c = 3.14;
    
    Model mm;
    mm.a = 20;
    mm.b = 60;
    mm.c = 1.0;
    
    m = mm;
    
    mm.a = 0;
    mm.b = 0;
    mm.c = 0.0;
    
    Assert::AreEqual<int>(20, m.a);
    Assert::AreEqual<int>(60, m.b);
    Assert::AreEqual<float>(1.0, m.c);
}
