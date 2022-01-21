#pragma once

#include "Serializable.h"

struct Serializable;

template<typename TType>
struct SerializableField
{
private:
    FieldData<TType>* _fieldData;

public:
    SerializableField(Serializable* serializable, const char* name);
    SerializableField(Serializable* serializable, const char* name, TType other);

    operator TType() const;
    SerializableField<TType>& operator=(TType other);
    bool operator==(SerializableField<TType>& rvalue) const;
    bool operator==(TType& rvalue) const;
};

#define DECLARE_VAR(type, name) \
SerializableField<type> name = SerializableField<type>(this, #name);

#define DECLARE_VAR_VAL(type, name, defaultValue) \
SerializableField<type> name = SerializableField<type>(this, #name, defaultValue);
