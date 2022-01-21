#pragma once

class ImplSerializableTests
{
public:
    static void TestSerializable();
    static void TestSerializableOrder();
    static void TestSerializeStruct();
    static void TestDeserializeStruct();
    static void TestCopyingStructValue();
    static void TestStringSerialization();
    static void TestStringDeserialization();
//    static void TestByteArraySerialization();
};

#define DECLARE_SERIALIZABLE_TESTS() \
DECLARE_TEST(SerializableTests, TestSerializable) \
DECLARE_TEST(SerializableTests, TestSerializableOrder) \
DECLARE_TEST(SerializableTests, TestSerializeStruct) \
DECLARE_TEST(SerializableTests, TestDeserializeStruct) \
DECLARE_TEST(SerializableTests, TestCopyingStructValue) \
DECLARE_TEST(SerializableTests, TestStringSerialization) \
DECLARE_TEST(SerializableTests, TestStringDeserialization) \
//DECLARE_TEST(SerializableTests, TestByteArraySerialization)
