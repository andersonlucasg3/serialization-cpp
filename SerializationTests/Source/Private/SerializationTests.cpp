#if !defined(__APPLE__)

#include "CppUnitTest.h"

#include "Implementations/TestsImplementations.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SerializationTests
{
	TEST_CLASS(SerializationTests)
	{
	public:
		
		TEST_METHOD(TestSerializable)
		{
            TestsImplementations::TestSerializable();
		}

		TEST_METHOD(TestSerializableOrder)
		{
			TestsImplementations::TestSerializableOrder();
		}
	};
}

#endif
