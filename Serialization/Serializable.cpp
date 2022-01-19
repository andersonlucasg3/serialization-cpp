#include "Serializable.h"

#pragma region FieldData

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

#pragma endregion

#pragma region Serializable

Serializable::Serializable()
{
    _reflectedMembers = list<BaseFieldData*>();
}

Serializable::~Serializable()
{
    for (BaseFieldData* element : _reflectedMembers)
    {
        delete element;
    }
    
    _reflectedMembers.clear();
}

#pragma endregion

#pragma region SerializableField

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
void SerializableField<TType>::operator=(TType other)
{
    _value = other;
}

#pragma endregion

#define BASE_FIELD_DATA(return) \
template return BaseFieldData

#define FIELD_DATA(return, type) \
template return FieldData<type>

#define SERIALIZATION_FIELD(return, type) \
template return SerializableField<type>

#define INSTANTIATE_ALL(type) \
BASE_FIELD_DATA(FieldData<type>&)::As<type>(); \
\
FIELD_DATA(, type)::FieldData(type*, const char*); \
FIELD_DATA(const char*, type)::GetName() const; \
\
SERIALIZATION_FIELD(, type)::SerializableField(Serializable*, const char*); \
SERIALIZATION_FIELD(, type)::SerializableField(Serializable*, const char*, type); \
SERIALIZATION_FIELD(type, type)::operator->() const; \
SERIALIZATION_FIELD(void, type)::operator=(type other);

INSTANTIATE_ALL(byte)
INSTANTIATE_ALL(unsigned short)
INSTANTIATE_ALL(short)
INSTANTIATE_ALL(unsigned int)
INSTANTIATE_ALL(int)
INSTANTIATE_ALL(unsigned long)
INSTANTIATE_ALL(long)
INSTANTIATE_ALL(unsigned long long)
INSTANTIATE_ALL(long long)
INSTANTIATE_ALL(float)
INSTANTIATE_ALL(double)
