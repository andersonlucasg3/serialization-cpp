#pragma once

#include "Serializable.h"

struct Model : public Serializable
{
public:
    DECLARE_VAR(int, a)
    DECLARE_VAR(int, b)
    DECLARE_VAR(float, c)
};

class TestsImplementations
{
public:
    static void TestFieldData();
    static void TestSerializable();
    static void TestSerializableOrder();
    static void TestSerializeStruct();
};
