#pragma once

class Assert
{
public:
    template<typename TType>
    static void AreEqual(TType value1, TType value2);
};