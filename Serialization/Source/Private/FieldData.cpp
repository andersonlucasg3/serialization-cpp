#include "FieldData.h"

#include <cstring>

BaseFieldData::~BaseFieldData() = default;

template<typename TType>
FieldData<TType>& BaseFieldData::As()
{
    return *reinterpret_cast<FieldData<TType>*>(this);
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
size_t& FieldData<TType>::PeekData(uint8_t* from, size_t& currentSize)
{
    memcpy(_ptr, from+currentSize, _typeSize);
    currentSize += _typeSize;
    return currentSize;
}

#define INSTANTIATE_ALL(type) \
template struct FieldData<type>; \
template FieldData<type>& BaseFieldData::As<type>();

#include "TemplateInstantiation.hpp"
