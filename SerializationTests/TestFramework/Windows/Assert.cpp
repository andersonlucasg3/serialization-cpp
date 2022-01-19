#include "TestFramework/Assert.h"

#include "CppUnitTest.h"

template<typename TType>
void Assert::AreEqual(TType value1, TType value2)
{

}

INSTANTIATE_ALL(void, int)
INSTANTIATE_ALL(void, float)
INSTANTIATE_ALL(void, const char*)