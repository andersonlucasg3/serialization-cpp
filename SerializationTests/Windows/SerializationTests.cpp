#if !defined(__APPLE__)
#include "CppUnitTest.h"

#include "Serializable.h"
#include "Implementations/TestsImplementations.h"

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
