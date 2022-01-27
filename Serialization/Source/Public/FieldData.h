#pragma once

#include <string>

#include "MemoryBuffer.h"

template<typename TType> struct FieldData;

struct BaseFieldData
{
public:
    virtual ~BaseFieldData() = default;

    virtual size_t GetSize() = 0;
    virtual size_t& PutData(uint8_t* into, size_t& currentSize) const = 0;
    virtual size_t& PeekData(uint8_t* from, size_t& currentSize) = 0;
    virtual void CopyFrom(const BaseFieldData& other) = 0;
    
    BaseFieldData& operator=(const BaseFieldData& other)
    {
        CopyFrom(other);

        return *this;
    }
};

extern size_t STRING_LENGTH_SIZE;

template<typename TType>
struct FieldData : public BaseFieldData
{
private:
	TType* _ptr;
    size_t _typeSize;
    const char* _name;
    
    void CopyCStr(const char* input, const char** output)
    {
        if (input == nullptr)
        {
            *output = nullptr;

            return;
        }

        size_t bytesLen = strlen(input) + 1;
        *output = new char[bytesLen];
        strcpy((char*)*output, input);
    }

    void FreeCStr(const char** input)
    {
        if (*input == nullptr) return;

        delete[] *input;

        *input = nullptr;
    }

    void CalculateValueSize()
    {
        _typeSize = sizeof(TType);
    }

    size_t& PutDataString(const char* ptr, size_t typeSize, size_t& currentSize, uint8_t* into) const
    {
        uint32_t stringLength = typeSize - STRING_LENGTH_SIZE;
        memcpy(into+currentSize, &stringLength, STRING_LENGTH_SIZE);
        currentSize += STRING_LENGTH_SIZE;
        if (stringLength > 0)
        {
            memcpy(into+currentSize, ptr, stringLength);
            currentSize += stringLength;
        }
        return currentSize;
    }

    size_t& PeekDataString(const char** ptr, size_t& currentSize, uint8_t* from)
    {
        uint32_t stringLength;
        memcpy(&stringLength, from+currentSize, STRING_LENGTH_SIZE);
        currentSize += STRING_LENGTH_SIZE;

        FreeCStr(ptr);

        size_t bytesLen = stringLength + 1;
        *ptr = new char[bytesLen];
        memset((void*)(*ptr+stringLength), 0, sizeof(char));

        memcpy((void*)*ptr, from+currentSize, stringLength);
        currentSize += stringLength;

        return currentSize;
    }

public:
    static FieldData<TType>& From(BaseFieldData& other) { return reinterpret_cast<FieldData<TType>&>(other); }
    static FieldData<TType>* From(BaseFieldData* other) { return reinterpret_cast<FieldData<TType>*>(other); }
    
    FieldData(const char* name)
    {
        _typeSize = 0;
        _name = nullptr;

        _ptr = new TType[1];

        if constexpr (std::is_same_v<TType, const char*>)
        {
            *_ptr = nullptr;
        }

        CopyCStr(name, &_name);

        CalculateValueSize();
    }

    ~FieldData() override
    {
        delete[] _name;
        delete[] _ptr;
    }

    TType GetValue()
    {
        return *_ptr;
    }

    void SetValue(TType newValue)
    {
        *_ptr = newValue;
    }

    const char* GetName() const
    {
        return _name;
    }

    size_t GetSize() override
    {
        return _typeSize;
    }

    size_t& PutData(uint8_t* into, size_t& currentSize) const override
    {
        memcpy(into+currentSize, (void*)_ptr, _typeSize);
        currentSize += _typeSize;
        return currentSize;
    }

    size_t& PeekData(uint8_t* from, size_t& currentSize) override
    {
        memcpy((void*)_ptr, from+currentSize, _typeSize);
        currentSize += _typeSize;
        return currentSize;
    }

    void CopyFrom(const BaseFieldData& other) override
    {
        const FieldData<TType>& oft = (const FieldData<TType>&)(other);
        *_ptr = *oft._ptr;
    }

    FieldData<TType>& operator=(const FieldData<TType>& other)
    {
        CopyFrom((BaseFieldData&)other);

        return *this;
    }
};

template<> void FieldData<const char*>::CalculateValueSize();
template<> void FieldData<std::string>::CalculateValueSize();
template<> void FieldData<const char*>::SetValue(const char* newValue);
template<> void FieldData<std::string>::SetValue(std::string newValue);
template<> size_t FieldData<const char*>::GetSize();
template<> size_t FieldData<std::string>::GetSize();
template<> size_t FieldData<BaseBuffer>::GetSize();
template<> size_t& FieldData<const char*>::PutData(uint8_t* into, size_t& currentSize) const;
template<> size_t& FieldData<std::string>::PutData(uint8_t* into, size_t& currentSize) const;
template<> size_t& FieldData<BaseBuffer>::PutData(uint8_t* into, size_t& currentSize) const;
template<> size_t& FieldData<const char*>::PeekData(uint8_t* from, size_t& currentSize);
template<> size_t& FieldData<std::string>::PeekData(uint8_t* from, size_t& currentSize);
template<> size_t& FieldData<BaseBuffer>::PeekData(uint8_t* from, size_t& currentSize);
template<> void FieldData<const char*>::CopyFrom(const BaseFieldData& other);

template<> FieldData<const char*>::~FieldData()
{
    delete[] _name;

    FreeCStr(_ptr);

    delete[] _ptr;
}
