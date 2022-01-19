#pragma once

#include <list>
#include <string>

using namespace std;

template<typename TType>
struct FieldData;

struct BaseFieldData
{
public:
    template<typename TType>
    FieldData<TType>& As();
};

template<typename TType>
struct FieldData : public BaseFieldData
{
private:
	TType* _ptr;
    string _name;

public:
    FieldData(TType* ptr, const char* name);
    const char* GetName() const;
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
	std::list<BaseFieldData*> _reflectedMembers;

public:
	Serializable();
    ~Serializable();

	template<typename TType>
	friend struct SerializableField;
};

template<typename TType>
struct SerializableField
{
private:
	TType _value;

public:
	SerializableField(Serializable* const serializable, const char* name);
	SerializableField(Serializable* const serializable, const char* name, TType other);

	TType operator->() const;
	void operator=(TType other);
};

#define DECLARE_VAR(type, name) \
SerializableField<type> name = SerializableField<type>(this, #name);

#define DECLARE_VAR_VAL(type, name, defaultValue) \
SerializableField<type> name = SerializableField<type>(this, #name, defaultValue);
