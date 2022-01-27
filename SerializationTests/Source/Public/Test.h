#pragma once

class Test
{
public:
    template<typename TType> static void AreEqual(TType value1, TType value2);
    template<typename TType> static void AreNotEqual(TType value1, TType value2);
    static void IsTrue(bool isTrue);
};

#pragma region Implementation

#include <string>
#include <sstream>
#include <cstdio>
#include <cstdlib>

#include "MemoryBuffer.h"

template<typename TType> struct MemoryBuffer;

#define DECLARE_ARE_EQUAL(type) \
void CheckAreEqual(type value1, type value2); \
void CheckAreEqual(MemoryBuffer<type> value1, MemoryBuffer<type> value2);

#define DECLARE_ARE_NOT_EQUAL(type) \
void CheckAreNotEqual(type value1, type value2);

void CheckIsTrue(bool isTrue, const char* message);

#define DECLARE_ALL(type) \
DECLARE_ARE_EQUAL(type) \
DECLARE_ARE_NOT_EQUAL(type)

DECLARE_ALL(const char*)
DECLARE_ALL(std::string)
DECLARE_ALL(uint8_t)
DECLARE_ALL(int8_t)
DECLARE_ALL(uint16_t)
DECLARE_ALL(int16_t)
DECLARE_ALL(uint32_t)
DECLARE_ALL(int32_t)
DECLARE_ALL(uint64_t)
DECLARE_ALL(int64_t)
DECLARE_ALL(size_t)
DECLARE_ALL(float)
DECLARE_ALL(double)
DECLARE_ALL(uint8_t*)

template<typename TType>
void Test::AreEqual(TType value1, TType value2)
{
    if constexpr (std::is_base_of_v<BaseBuffer, TType>)
    {
        std::stringstream ss;
        ss << "byte array value1 " <<
            value1.GetBuffer() << " with length " <<
            value1.Length() << " is not equal to byte array value2 " <<
            value2.GetBuffer() << " with length " << value2.Length();
        

        CheckIsTrue(value1 == value2, ss.str().c_str());

        return;
    }

    CheckAreEqual(value1, value2);
}

template<typename TType>
void Test::AreNotEqual(TType value1, TType value2)
{
    CheckAreNotEqual(value1, value2);
}

#pragma endregion
