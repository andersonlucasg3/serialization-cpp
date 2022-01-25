#include "SerializableTests.h"

#include <cstring>

#include "Assert.h"
#include "Serializable.h"
#include "SerializableField.h"
#include "MemoryBuffer.h"

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

void CompareStreams(uint8_t* manuallyGeneratedData, uint8_t* serializedData, size_t totalSize)
{
    for (int index = 0; index < totalSize; ++index)
    {
        Assert::AreEqual(*(manuallyGeneratedData + index), *(serializedData + index));
    }
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

    CompareStreams(compare, serializedData, m.GetTotalSizeInBytes());
    
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
    
    m.a = 0;
    m.b = 0;
    m.c = 0.0;
    
    Assert::AreEqual<int>(0, mm.a);
    Assert::AreEqual<int>(0, mm.b);
    Assert::AreEqual<float>(.0, mm.c);
    
    Assert::AreEqual<int>(m.a, mm.a);
    Assert::AreEqual<int>(m.b, mm.b);
    Assert::AreEqual<float>(m.c, mm.c);
}

struct Person : public Serializable
{
public:
    DECLARE_VAR(uint8_t, age);
    DECLARE_VAR(const char*, name);
    DECLARE_VAR(string, address);
};

void ImplSerializableTests::TestStringSerialization()
{
    Person person;
    person.age = 10;
    person.name = "Anderson Lucas C. Ramos";
    person.address = "Rio de Janeiro";
    
    uint8_t* serializedPerson = person.Serialize();
    
    uint8_t* manualSerializedPerson = new uint8_t[person.GetTotalSizeInBytes()];
    
    size_t position = 0;
    uint8_t age = 10;
    const char *name = "Anderson Lucas C. Ramos";
    uint32_t nameLen = strlen(name);
    string address = "Rio de Janeiro";
    uint32_t addressLen = address.size();
    
    memcpy(manualSerializedPerson, &age, sizeof(uint8_t));
    position += sizeof(uint8_t);
    
    memcpy(manualSerializedPerson+position, &nameLen, sizeof(uint32_t));
    position += sizeof(uint32_t);
    
    memcpy(manualSerializedPerson+position, name, nameLen);
    position += nameLen;
    
    memcpy(manualSerializedPerson+position, &addressLen, sizeof(uint32_t));
    position += sizeof(uint32_t);

    memcpy(manualSerializedPerson+position, address.c_str(), addressLen);
    position += addressLen;
    
    Assert::AreEqual(position, person.GetTotalSizeInBytes());
    
    CompareStreams(manualSerializedPerson, serializedPerson, person.GetTotalSizeInBytes());
    
    delete[] serializedPerson;
    delete[] manualSerializedPerson;
}

void ImplSerializableTests::TestStringDeserialization()
{
    Person person;
    person.age = 10;
    person.name = "Anderson Lucas C. Ramos";
    person.address = "Rio de Janeiro";
    
    uint8_t* serializedPerson = person.Serialize();
    
    Assert::AreEqual<size_t>(46, person.GetTotalSizeInBytes());
    
    Person deserializedPerson;
    
    deserializedPerson.Deserialize(serializedPerson);
    
    Assert::AreEqual<uint8_t>(person.age, deserializedPerson.age);
    Assert::AreEqual<const char*>(person.name, deserializedPerson.name);
    Assert::AreEqual<string>(person.address, deserializedPerson.address);
}

struct StreamSerializable : public Serializable
{
public:
    DECLARE_VAR(int, someInt)
    DECLARE_VAR(MemoryBuffer<uint8_t>, stringAsByteArray)
    DECLARE_VAR(const char*, stringJustForFun)
};

void ImplSerializableTests::TestMemoryBufferSerialization()
{
    const char *strContent = "I just want to test byte array serialization";
    size_t len = strlen(strContent);
    
    const char* stringForFun = "Some string to make it fun";
    
    uint8_t* strAsBytes = new uint8_t[len];
    memcpy(strAsBytes, strContent, len);
    
    StreamSerializable toSerialize;
    toSerialize.someInt = 128;
    toSerialize.stringAsByteArray = MemoryBuffer<uint8_t>(strAsBytes, len, false);
    toSerialize.stringJustForFun = stringForFun;
    
    uint8_t* serializedStream = toSerialize.Serialize();
    
    StreamSerializable toDeserialize;
    toDeserialize.Deserialize(serializedStream);
    
    Assert::AreEqual<int>(128, toDeserialize.someInt);
    
    MemoryBuffer<uint8_t> byteArray = toDeserialize.stringAsByteArray.operator MemoryBuffer<uint8_t>();
    
    const uint8_t* deserializedBytes = byteArray.GetBuffer();
    char* deserializedStrContent = new char[byteArray.Length() + 1];
    memset(deserializedStrContent+byteArray.Length(), 0, 1);
    memcpy(deserializedStrContent, deserializedBytes, byteArray.Length());
    
    Assert::AreEqual(strContent, const_cast<const char*>(deserializedStrContent));
    
    Assert::AreEqual<const char*>(stringForFun, toDeserialize.stringJustForFun);
}
