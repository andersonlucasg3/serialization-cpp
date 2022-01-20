#if !defined(__APPLE__)

#include "TestFramework/Assert.h"

#include "CppUnitTest.h"

template<typename TType>
void Assert::AreEqual(TType value1, TType value2)
{

}

#define INSTANTIATE_ALL(type) \
template void Assert::AreEqual(type, type);

#include "TemplateInstantiation.hpp"

#endif
