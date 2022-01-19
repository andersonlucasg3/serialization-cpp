#include "TestsImplementations.h"
#include "TestFramework/Assert.h"

void TestsImplementations::TestSerializable()
{
    Model m = Model();
    Assert::AreEqual(3, (int)m._reflectedMembers.size());
}

void TestsImplementations::TestSerializableOrder()
{
    Model m = Model();
    auto iterator = m._reflectedMembers.begin();
    Assert::AreEqual("a", (*iterator)->As<int>().GetName());
    advance(iterator, 1);
    Assert::AreEqual("b", (*iterator)->As<int>().GetName());
    advance(iterator, 1);
    Assert::AreEqual("c", (*iterator)->As<float>().GetName());
}
