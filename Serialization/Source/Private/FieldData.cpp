#include "FieldData.h"

#include <cstring>

BaseFieldData& BaseFieldData::operator=(const BaseFieldData &other)
{
    CopyFrom(other);

    return *this;
}

template<typename TType>
FieldData<TType>& FieldData<TType>::From(BaseFieldData& other)
{
    return reinterpret_cast<FieldData<TType>&>(other);
}

template<typename TType>
FieldData<TType>* FieldData<TType>::From(BaseFieldData* other)
{
    return reinterpret_cast<FieldData<TType>*>(other);
}

template<typename TType>
FieldData<TType>::FieldData(TType* ptr, const char *name)
{
    _ptr = ptr;
    _typeSize = sizeof(TType);
    _name = string(name);
}

template<typename TType>
const char* FieldData<TType>::GetName() const
{
    return _name.c_str();
}

template<typename TType>
TType FieldData<TType>::GetValue() const
{
    return *_ptr;
}

template<typename TType>
void FieldData<TType>::SetValue(TType newValue) const
{
    *_ptr = newValue;
}

template<typename TType>
size_t FieldData<TType>::GetSize() const
{
    return _typeSize;
}

template<typename TType>
size_t& FieldData<TType>::PutData(uint8_t* into, size_t& currentSize) const
{
    memcpy(into+currentSize, _ptr, _typeSize);
    currentSize += _typeSize;
    return currentSize;
}

template<typename TType>
size_t& FieldData<TType>::PeekData(uint8_t* from, size_t& currentSize) const
{
    memcpy(_ptr, from+currentSize, _typeSize);
    currentSize += _typeSize;
    return currentSize;
}

template<typename TType>
void FieldData<TType>::CopyFrom(const BaseFieldData& other)
{
    const FieldData<TType>& oft = (const FieldData<TType>&)(other);
    *_ptr = *oft._ptr;
    // _typeSize should never change;
    _name = oft._name;
}

template<typename TType>
FieldData<TType>& FieldData<TType>::operator=(const FieldData<TType>& other)
{
    CopyFrom((BaseFieldData&)other);

    return *this;
}

#define INSTANTIATE_ALL(type) \
template struct FieldData<type>;

#include "TemplateInstantiation.hpp"
