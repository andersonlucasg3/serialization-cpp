#include "SerializableField.h"
#include "Serializable.h"
#include "FieldData.h"

template<typename TType>
SerializableField<TType>::SerializableField(Serializable* const serializable, const char* name)
{
    FieldData<TType>* typeInfo = new FieldData<TType>(&_value, name);
    list<BaseFieldData*>& members = serializable->_reflectedMembers;
    members.insert(end(members), typeInfo);
}

template<typename TType>
SerializableField<TType>::SerializableField(Serializable* serializable, const char* name, TType other) : SerializableField(serializable, name)
{
    _value = other;
}

template<typename TType>
TType SerializableField<TType>::operator->() const
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
