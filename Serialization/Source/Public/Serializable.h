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
    
    [[nodiscard]] uint8_t* Serialize() const;
    
    [[nodiscard]] const list<BaseFieldData*>& GetFields() const;
    [[nodiscard]] size_t GetTotalSizeInBytes() const;

	template<typename TType>
	friend struct SerializableField;
};
