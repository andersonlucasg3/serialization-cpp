#if !defined(__APPLE__)

#include "Assert.h"

#include "CppUnitTest.h"

typedef Microsoft::VisualStudio::CppUnitTestFramework::Assert VSAssert;

#define TEXT(str) L##str

template<typename TType>
void Assert::AreEqual(TType value1, TType value2)
{
	VSAssert::AreEqual(value1, value2, TEXT(""));
}

template<> inline std::wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString<uint16_t>(const uint16_t& t) { RETURN_WIDE_STRING(t); }

#define INSTANTIATE_ALL(type) \
template void Assert::AreEqual(type, type);

#include "TemplateInstantiation.hpp"

#endif
