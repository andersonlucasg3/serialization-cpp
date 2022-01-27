#pragma once

#include <list>

#include "FieldData.h"

struct Serializable
{
private:
	std::list<BaseFieldData*>* _fields;
    
    template<typename TType>
    void AddField(FieldData<TType>* fieldData)
    {
        std::list<BaseFieldData*>::iterator endIndex = end(*_fields);

        _fields->insert(endIndex, fieldData);
    }

public:
	Serializable();
    ~Serializable();
    
    uint8_t* Serialize() const;
    void Deserialize(uint8_t* data);
    
    const std::list<BaseFieldData*> GetFields() const;
    size_t GetTotalSizeInBytes() const;
    
    Serializable& operator=(const Serializable& other);

	template<typename TType>
	friend struct SerializableField;
};
