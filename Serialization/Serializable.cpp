#include "Serializable.h"

template<typename TType>
void Serializable::AddField(FieldData<TType>* fieldData)
{
    _dataSizeInBytes += sizeof(TType);
    
    auto endIndex = end(_fields);
    
    _fields.insert(endIndex, fieldData);
}

Serializable::Serializable()
{
    _fields = list<BaseFieldData*>();
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
    // TODO(anderson): implement
    return nullptr;
}

const list<BaseFieldData*>& Serializable::GetFields() const
{
    return _fields;
}

#define INSTANTIATE_ALL(type) \
template void Serializable::AddField<type>(FieldData<type>*);

#include "TemplateInstantiation.hpp"
