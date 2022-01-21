#include "Serializable.h"

template<typename TType>
void Serializable::AddField(FieldData<TType>* fieldData)
{
    list<BaseFieldData*>::iterator endIndex = end(_fields);
    
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
    uint8_t* buffer = new uint8_t[GetTotalSizeInBytes()];
    size_t position = 0;
    for (BaseFieldData* element : _fields)
    {
        position = element->PutData(buffer, position);
    }
    return buffer;
}

void Serializable::Deserialize(uint8_t *data)
{
    size_t position = 0;
    for (BaseFieldData* element : _fields)
    {
        position = element->PeekData(data, position);
    }
}

const list<BaseFieldData*>& Serializable::GetFields() const
{
    return _fields;
}

size_t Serializable::GetTotalSizeInBytes() const
{
    size_t dataSizeInBytes = 0;
    
    for (BaseFieldData* field : _fields)
    {
        dataSizeInBytes += field->GetSize();
    }
    
    return dataSizeInBytes;
}

Serializable& Serializable::operator=(const Serializable &other)
{
    list<BaseFieldData*>::const_iterator iteratorThis = _fields.begin();
    list<BaseFieldData*>::const_iterator iteratorOther = other._fields.begin();
    
    for (int index = 0; index < _fields.size(); ++index)
    {
        if (index > 0)
        {
            advance(iteratorThis, 1);
            advance(iteratorOther, 1);
        }
        
        BaseFieldData* dataTo = *iteratorThis;
        BaseFieldData* dataFrom = *iteratorOther;
        
        dataTo->CopyFrom(*dataFrom);
    }
    
    return *this;
}

#define INSTANTIATE_ALL(type) \
template void Serializable::AddField<type>(FieldData<type>*);

#include "TemplateInstantiation.hpp"
