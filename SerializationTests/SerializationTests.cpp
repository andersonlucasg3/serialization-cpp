#include "CppUnitTest.h"
#include "Serializable.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SerializationTests
{
	struct Model : public Serializable
	{
	public:
		DECLARE_VAR(int, a)
		DECLARE_VAR(int, b)
		DECLARE_VAR(float, c)
	};

	TEST_CLASS(SerializationTests)
	{
	public:
		
		TEST_METHOD(TestSerializable)
		{
			Model m = Model();
			Assert::AreEqual(3, (int)m._reflectedMembers.size());
		}
	};
}
