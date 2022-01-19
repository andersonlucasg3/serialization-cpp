#include "FieldData.h"

template<typename TType>
FieldData<TType>& BaseFieldData::As()
{
    return *reinterpret_cast<FieldData<TType>*>(this);
}

template<typename TType>
FieldData<TType>::FieldData(TType* ptr, const char *name)
{
    _ptr = ptr;
    _name = string(name);
}

template<typename TType>
const char* FieldData<TType>::GetName() const
{
    return _name.c_str();
}

#define INSTANTIATE_ALL(type) \
template struct FieldData<type>; \
template FieldData<type>& BaseFieldData::As<type>();

#include "TemplateInstantiation.hpp"
