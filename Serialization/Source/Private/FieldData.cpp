#include "FieldData.h"

#include <cstring>
#include "MemoryBuffer.h"

size_t STRING_LENGTH_SIZE = sizeof(uint32_t);

BaseFieldData& BaseFieldData::operator=(const BaseFieldData &other)
{
    CopyFrom(other);

    return *this;
}

template<typename TType>
void FieldData<TType>::CopyCStr(const char* input, const char** output)
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

template<typename TType>
void FieldData<TType>::FreeCStr(const char** input)
{
    if (*input == nullptr) return;
    
    delete[] *input;
    
    *input = nullptr;
}

template<typename TType>
void FieldData<TType>::CalculateValueSize()
{
    _typeSize = sizeof(TType);
}

template<>
void FieldData<const char*>::CalculateValueSize()
{
    if (*_ptr == nullptr)
    {
        if (_typeSize > STRING_LENGTH_SIZE)
        {
            _typeSize = STRING_LENGTH_SIZE;
        }
        
        return;
    }
    
    size_t valueStrLen = strlen(*_ptr);
    size_t typeSize = STRING_LENGTH_SIZE + valueStrLen;
    
    if (_typeSize != typeSize)
    {
        _typeSize = typeSize;
    }
}

template<>
void FieldData<string>::CalculateValueSize()
{
    size_t valueStrLen = _ptr->size();
    size_t typeSize = STRING_LENGTH_SIZE + valueStrLen;
    
    if (_typeSize != typeSize)
    {
        _typeSize = typeSize;
    }
}

template<typename TType>
FieldData<TType>& FieldData<TType>::From(BaseFieldData& other)
{
    return reinterpret_cast<FieldData<TType>&>(other);
}

template<typename TType>
FieldData<TType>* FieldData<TType>::From(BaseFieldData* other)
{
    return reinterpret_cast<FieldData<TType>*>(other);
}

template<typename TType>
FieldData<TType>::FieldData(const char *name)
{
    _ptr = new TType[1];
    
    if constexpr (std::is_same_v<TType, const char*>)
    {
        *_ptr = nullptr;
    }
    
    CopyCStr(name, &_name);
    
    CalculateValueSize();
}

template<typename TType>
FieldData<TType>::~FieldData<TType>()
{
    delete[] _name;
    delete[] _ptr;
}

template<>
FieldData<const char*>::~FieldData()
{
    delete[] _name;
    
    FreeCStr(_ptr);
    
    delete[] _ptr;
}

template<typename TType>
const char* FieldData<TType>::GetName() const
{
    return _name;
}

template<typename TType>
TType FieldData<TType>::GetValue() const
{
    return *_ptr;
}

template<typename TType>
void FieldData<TType>::SetValue(TType newValue)
{
    *_ptr = newValue;
}

template<>
void FieldData<const char*>::SetValue(const char* newValue)
{
    FreeCStr(_ptr);
    
    if (newValue == nullptr)
    {
        CalculateValueSize();
        
        return;
    }
    
    CopyCStr(newValue, _ptr);
    
    CalculateValueSize();
}

template<>
void FieldData<string>::SetValue(string newValue)
{
    *_ptr = newValue;
    
    CalculateValueSize();
}

template<typename TType>
size_t FieldData<TType>::GetSize()
{
    return _typeSize;
}

template<>
size_t FieldData<const char*>::GetSize()
{
    CalculateValueSize();
    
    return _typeSize;
}

template<>
size_t FieldData<string>::GetSize()
{
    CalculateValueSize();
    
    return _typeSize;
}

template<>
size_t FieldData<BaseBuffer>::GetSize()
{
    if (_ptr == nullptr) return 0;
    return sizeof(size_t) + _ptr->Length();
}

template<typename TType>
size_t& FieldData<TType>::PutData(uint8_t* into, size_t& currentSize) const
{
    memcpy(into+currentSize, (void*)_ptr, _typeSize);
    currentSize += _typeSize;
    return currentSize;
}

template<typename TType>
size_t& FieldData<TType>::PutDataString(const char* ptr, size_t typeSize, size_t& currentSize, uint8_t* into) const
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

template<>
size_t& FieldData<const char*>::PutData(uint8_t* into, size_t& currentSize) const
{
    return PutDataString(*_ptr, _typeSize, currentSize, into);
}

template<>
size_t& FieldData<string>::PutData(uint8_t* into, size_t& currentSize) const
{
    return PutDataString(_ptr->c_str(), _typeSize, currentSize, into);
}

template<>
size_t& FieldData<BaseBuffer>::PutData(uint8_t* into, size_t& currentSize) const
{
    if (_ptr == nullptr) return currentSize;
    
    size_t len = _ptr->Length();
    memcpy(into+currentSize, &len, sizeof(size_t));
    currentSize += sizeof(size_t);
    
    memcpy(into+currentSize, _ptr->GetBuffer(), len);
    currentSize += len;
    
    return currentSize;
}

template<typename TType>
size_t& FieldData<TType>::PeekData(uint8_t* from, size_t& currentSize)
{
    memcpy((void*)_ptr, from+currentSize, _typeSize);
    currentSize += _typeSize;
    return currentSize;
}

template<typename TType>
size_t& FieldData<TType>::PeekDataString(const char** ptr, size_t& currentSize, uint8_t* from)
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

template<>
size_t& FieldData<const char*>::PeekData(uint8_t* from, size_t& currentSize)
{
    return PeekDataString(_ptr, currentSize, from);
}

template<>
size_t& FieldData<string>::PeekData(uint8_t* from, size_t& currentSize)
{
    const char* str = nullptr;
    currentSize = PeekDataString(&str, currentSize, from);
    *_ptr = str;
    return currentSize;
}

template<>
size_t& FieldData<BaseBuffer>::PeekData(uint8_t* from, size_t& currentSize)
{
    size_t len;
    memcpy(&len, from+currentSize, sizeof(size_t));
    currentSize += sizeof(size_t);
    
    uint8_t* buffer = new uint8_t[len];
    memcpy(buffer, from+currentSize, len);
    currentSize += len;
    
    _ptr->Set(buffer, len, false);
    
    return currentSize;
}

template<typename TType>
void FieldData<TType>::CopyFrom(const BaseFieldData& other)
{
    const FieldData<TType>& oft = (const FieldData<TType>&)(other);
    *_ptr = *oft._ptr;
}

template<>
void FieldData<const char*>::CopyFrom(const BaseFieldData& other)
{
    const FieldData<const char*>& oft = (const FieldData<const char*>&)(other);
    
    FreeCStr(_ptr);
    
    if (*oft._ptr != nullptr)
    {
        CopyCStr(*oft._ptr, _ptr);
    }
}

template<typename TType>
FieldData<TType>& FieldData<TType>::operator=(const FieldData<TType>& other)
{
    CopyFrom((BaseFieldData&)other);

    return *this;
}

#define INSTANTIATE_ALL(type) \
template struct FieldData<type>; \
template struct FieldData<MemoryBuffer<type>>;

#include "TemplateInstantiation.hpp"
