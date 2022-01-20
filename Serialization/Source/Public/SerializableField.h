#pragma once

struct Serializable;

template<typename TType>
struct SerializableField
{
private:
    TType _value;

public:
    SerializableField(Serializable* serializable, const char* name);
    SerializableField(Serializable* serializable, const char* name, TType other);

    TType operator->() const;
    SerializableField<TType>& operator=(TType other);
};

#define DECLARE_VAR(type, name) \
SerializableField<type> name = SerializableField<type>(this, #name);

#define DECLARE_VAR_VAL(type, name, defaultValue) \
SerializableField<type> name = SerializableField<type>(this, #name, defaultValue);
