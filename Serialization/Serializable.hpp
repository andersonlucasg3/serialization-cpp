#pragma once

#include <list>

using namespace std;

struct BaseTypeInfo {};

template<typename TType>
struct FieldData : public BaseTypeInfo
{
private:
	TType* _ptr;

public:

	FieldData(TType* ptr)
	{
		_ptr = ptr;
	}
};

template<typename TType>
struct SerializableField;

struct Serializable
{
#ifdef _TESTS
public:
#else
private:
#endif
	std::list<BaseTypeInfo> _reflectedMembers;

public:
	Serializable();

	template<typename TType>
	friend struct SerializableField;
};

template<typename TType>
struct SerializableField
{
private:
	TType _value;

public:
	SerializableField(Serializable* const serializable);
	SerializableField(Serializable* const serializable, TType& other);

	TType operator->() const;
	void operator=(TType other);
};

#define DECLARE_VAR(type, name) \
	SerializableField<type> name = SerializableField<type>(this);

#define DECLARE_VAR_VAL(type, name, defaultValue) \
	SerializableField<type> name = SerializableField<type>(this, defaultValue);

#pragma region Serializable

Serializable::Serializable()
{
	_reflectedMembers = list<BaseTypeInfo>();
}

#pragma endregion

#pragma region SerializableField

template<typename TType>
SerializableField<TType>::SerializableField(Serializable* serializable)
{
	FieldData<TType> typeInfo = FieldData<TType>(&_value);
	list<BaseTypeInfo>& members = serializable->_reflectedMembers;
	members.insert(end(members), typeInfo);
}

template<typename TType>
SerializableField<TType>::SerializableField(Serializable* serializable, TType& other)
{
	_value = other;
	SerializableField<TType>::SerializableField(serializable);
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
