#include "Serializable.h"

template<typename TType>
void Serializable::AddField(FieldData<TType>* fieldData)
{
    _dataSizeInBytes += sizeof(TType);
    
    list<BaseFieldData*>::iterator endIndex = end(_fields);
    
    _fields.insert(endIndex, fieldData);
}

Serializable::Serializable()
{
    _fields = list<BaseFieldData*>();
    _dataSizeInBytes = 0;
}

Serializable::~Serializable()
{
    for (BaseFieldData* element : _fields)
    {
        delete element;
    }
    
    _fields.clear();
}

uint8_t *Serializable::Serialize() const
{
    uint8_t* buffer = new uint8_t[_dataSizeInBytes];
    size_t position = 0;
    for (BaseFieldData* element : _fields)
    {
        position = element->PutData(buffer, position);
    }
    return buffer;
}

const list<BaseFieldData*>& Serializable::GetFields() const
{
    return _fields;
}

size_t Serializable::GetTotalSizeInBytes() const
{
    return _dataSizeInBytes;
}

#define INSTANTIATE_ALL(type) \
template void Serializable::AddField<type>(FieldData<type>*);

#include "TemplateInstantiation.hpp"
