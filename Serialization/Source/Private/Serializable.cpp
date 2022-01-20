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
    _dataSizeInBytes = 0;
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
    return _dataSizeInBytes;
}

Serializable& Serializable::operator=(const Serializable &other)
{
    list<BaseFieldData*>::const_iterator iteratorThis = _fields.begin();
    list<BaseFieldData*>::const_iterator iteratorOther = other._fields.begin();
    for (int index = 0; index < _fields.size(); ++index)
    {
        advance(iteratorThis, index);
        advance(iteratorOther, index);
        
        BaseFieldData* dataTo = *iteratorThis;
        BaseFieldData* dataFrom = *iteratorOther;
        
        *dataTo = *dataFrom;
    }
    
    _dataSizeInBytes = other._dataSizeInBytes;
    return *this;
}

#define INSTANTIATE_ALL(type) \
template void Serializable::AddField<type>(FieldData<type>*);

#include "TemplateInstantiation.hpp"
