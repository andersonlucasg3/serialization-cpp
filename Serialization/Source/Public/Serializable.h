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
    size_t _dataSizeInBytes;
    
    template<typename TType>
    void AddField(FieldData<TType>* fieldData);

public:
	Serializable();
    ~Serializable();
    
    uint8_t* Serialize() const;
    void Deserialize(uint8_t* data);
    
    const list<BaseFieldData*>& GetFields() const;
    size_t GetTotalSizeInBytes() const;
    
    Serializable& operator=(const Serializable& other);

	template<typename TType>
	friend struct SerializableField;
};
