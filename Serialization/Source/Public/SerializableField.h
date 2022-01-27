#pragma once

struct Serializable;
template<typename TType> struct FieldData;

template<typename TType>
struct SerializableField
{
private:
    FieldData<TType>* _fieldData;

public:
    SerializableField(Serializable* serializable, const char* name)
    {
        _fieldData = new FieldData<TType>(name);
        serializable->AddField(_fieldData);
    }
    
    SerializableField(Serializable* serializable, const char* name, TType other)
    {
        _fieldData->SetValue(other);
    }

    TType Get()
    {
        return std::move(_fieldData->GetValue());
    }
    
    void Set(TType newValue)
    {
        _fieldData->SetValue(newValue);
    }
    
    TType operator->()
    {
        return _fieldData->GetValue();
    }
    
    operator TType() const
    {
        return _fieldData->GetValue();
    }
    
    SerializableField<TType>& operator=(TType other)
    {
        _fieldData->SetValue(other);
        
        return *this;
    }
    
    bool operator==(SerializableField<TType>& rvalue) const
    {
        return _fieldData->GetValue() == rvalue._fieldData->GetValue();
    }
    
    bool operator==(TType& rvalue) const
    {
        return _fieldData->GetValue() == rvalue;
    }
};

#define DECLARE_VAR(type, name) \
SerializableField<type> name = SerializableField<type>(this, #name);

#define DECLARE_VAR_VAL(type, name, defaultValue) \
SerializableField<type> name = SerializableField<type>(this, #name, defaultValue);
