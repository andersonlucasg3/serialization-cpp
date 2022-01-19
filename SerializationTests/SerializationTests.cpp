#if !defined(__APPLE__)
#include "CppUnitTest.h"

#include "Serializable.hpp"
#include "TestsImplementations/TestsImplementations.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SerializationTests
{
	TEST_CLASS(SerializationTests)
	{
	public:
		
		TEST_METHOD(TestSerializable)
		{
            TestsImplementations::SerializationTests();
		}
	};
}

#endif
