#include "SerializableField.h"
#include "Serializable.h"
#include "FieldData.h"

template<typename TType>
SerializableField<TType>::SerializableField(Serializable* const serializable, const char* name)
{
    _fieldData = new FieldData<TType>(name);
    serializable->AddField(_fieldData);
}

template<typename TType>
SerializableField<TType>::SerializableField(Serializable* serializable, const char* name, TType other) : SerializableField(serializable, name)
{
    _fieldData->SetValue(other);
}

template<typename TType>
SerializableField<TType>::operator TType() const
{
    return _fieldData->GetValue();
}

template<typename TType>
SerializableField<TType>& SerializableField<TType>::operator=(TType other)
{
    _fieldData->SetValue(other);
    return *this;
}

template<typename TType>
bool SerializableField<TType>::operator==(SerializableField<TType>& rvalue) const
{
    return _fieldData->GetValue() == rvalue._fieldData->GetValue();
}

template<typename TType>
bool SerializableField<TType>::operator==(TType& rvalue) const
{
    return _fieldData->GetValue() == rvalue;
}

#define INSTANTIATE_ALL(type) \
template struct SerializableField<type>;

#include "TemplateInstantiation.hpp"
