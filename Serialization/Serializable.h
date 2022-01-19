#pragma once

#include <list>
#include <string>

#include "FieldData.h"
#include "SerializableField.h"

using namespace std;

struct Serializable
{
#ifdef _TESTS
public:
#else
private:
#endif
	std::list<BaseFieldData*> _reflectedMembers;

public:
	Serializable();
    ~Serializable();
    
    uint8_t* Serialize() const;

	template<typename TType>
	friend struct SerializableField;
};
