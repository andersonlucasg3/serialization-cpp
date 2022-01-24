#if !defined(__APPLE__)

#include "Assert.h"

#include "CppUnitTest.h"

#include "MemoryBuffer.h"
#include <string>

typedef Microsoft::VisualStudio::CppUnitTestFramework::Assert VSAssert;

#define TEXT(str) L##str

template<typename TType>
void Assert::AreEqual(TType value1, TType value2)
{
	VSAssert::AreEqual(value1, value2, TEXT(""));
}

template<typename TType>
void Assert::AreNotEqual(TType value1, TType value2)
{
	VSAssert::AreNotEqual(value1, value2, TEXT(""));
}

template<> inline std::wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString<uint16_t>(const uint16_t& t) { RETURN_WIDE_STRING(t); }
template<> inline std::wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString<uint16_t>(const uint16_t* t) { RETURN_WIDE_STRING(*t); }
template<> inline std::wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString<uint16_t>(uint16_t* t) { RETURN_WIDE_STRING(*t); }
template<> inline std::wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString<const char*>(const char** t) { RETURN_WIDE_STRING(*t); }
template<> inline std::wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString<std::string>(std::string* t) { RETURN_WIDE_STRING(t->c_str()); }

#define INSTANTIATE_ALL(type) \
template void Assert::AreEqual(type, type); \
template void Assert::AreNotEqual(type, type); \
template void Assert::AreEqual(type*, type*); \
template void Assert::AreNotEqual(type*, type*); \
template void Assert::AreEqual(MemoryBuffer<type>, MemoryBuffer<type>); \
template void Assert::AreNotEqual(MemoryBuffer<type>, MemoryBuffer<type>); \
template<> inline std::wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString<MemoryBuffer<type>>(const MemoryBuffer<type>& t) \
{ \
	std::wstringstream _s; \
	_s << "Memory<std::string> { length: "; \
	_s << t.Length(); \
	_s << " }"; \
	return _s.str(); \
}

#include "TemplateInstantiation.hpp"

#endif
