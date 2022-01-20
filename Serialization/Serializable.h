#pragma once

#include <list>
#include <string>

#include "FieldData.h"
#include "SerializableField.h"

using namespace std;

struct Serializable
{
private:
	list<BaseFieldData*> _fields;
    int _dataSizeInBytes;
    
    template<typename TType>
    void AddField(FieldData<TType>* fieldData);

public:
	Serializable();
    ~Serializable();
    
    uint8_t* Serialize() const;
    
    const list<BaseFieldData*>& GetFields() const;

	template<typename TType>
	friend struct SerializableField;
};
