#include "SerializableField.h"
#include "Serializable.h"
#include "FieldData.h"

template<typename TType>
SerializableField<TType>::SerializableField(Serializable* const serializable, const char* name)
{
    FieldData<TType>* fieldData = new FieldData<TType>(&_value, name);
    serializable->AddField(fieldData);
}

template<typename TType>
SerializableField<TType>::SerializableField(Serializable* serializable, const char* name, TType other) : SerializableField(serializable, name)
{
    _value = other;
}

template<typename TType>
SerializableField<TType>::operator TType() const
{
    return _value;
}

template<typename TType>
SerializableField<TType>& SerializableField<TType>::operator=(TType other)
{
    _value = other;
    return *this;
}

#define INSTANTIATE_ALL(type) \
template struct SerializableField<type>;

#include "TemplateInstantiation.hpp"
