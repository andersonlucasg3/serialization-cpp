#include "FieldData.h"

#include <utility>

size_t STRING_LENGTH_SIZE = sizeof(uint32_t);

template<> void FieldData<const char*>::CalculateValueSize()
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

template<> void FieldData<std::string>::CalculateValueSize()
{
    size_t valueStrLen = _ptr->size();
    size_t typeSize = STRING_LENGTH_SIZE + valueStrLen;

    if (_typeSize != typeSize)
    {
        _typeSize = typeSize;
    }
}

template<> void FieldData<const char*>::SetValue(const char* newValue)
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

template<> void FieldData<std::string>::SetValue(std::string newValue)
{
    *_ptr = std::move(newValue);

    CalculateValueSize();
}

template<> size_t FieldData<const char*>::GetSize()
{
    CalculateValueSize();

    return _typeSize;
}

template<> size_t FieldData<std::string>::GetSize()
{
    CalculateValueSize();

    return _typeSize;
}

template<> size_t FieldData<BaseBuffer>::GetSize()
{
    if (_ptr == nullptr) return 0;
    return sizeof(size_t) + _ptr->Length();
}

template<> size_t& FieldData<const char*>::PutData(uint8_t* into, size_t& currentSize) const
{
    return PutDataString(*_ptr, _typeSize, currentSize, into);
}

template<> size_t& FieldData<std::string>::PutData(uint8_t* into, size_t& currentSize) const
{
    return PutDataString(_ptr->c_str(), _typeSize, currentSize, into);
}

template<> size_t& FieldData<BaseBuffer>::PutData(uint8_t* into, size_t& currentSize) const
{
    if (_ptr == nullptr) return currentSize;

    size_t len = _ptr->Length();
    memcpy(into+currentSize, &len, sizeof(size_t));
    currentSize += sizeof(size_t);

    memcpy(into+currentSize, _ptr->GetBuffer(), len);
    currentSize += len;

    return currentSize;
}

template<> size_t& FieldData<const char*>::PeekData(uint8_t* from, size_t& currentSize)
{
    return PeekDataString(_ptr, currentSize, from);
}

template<> size_t& FieldData<std::string>::PeekData(uint8_t* from, size_t& currentSize)
{
    const char* str = nullptr;
    currentSize = PeekDataString(&str, currentSize, from);
    *_ptr = str;
    return currentSize;
}

template<> size_t& FieldData<BaseBuffer>::PeekData(uint8_t* from, size_t& currentSize)
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

template<> void FieldData<const char*>::CopyFrom(const BaseFieldData& other)
{
    const FieldData<const char*>& oft = (const FieldData<const char*>&)(other);

    FreeCStr(_ptr);

    if (*oft._ptr != nullptr)
    {
        CopyCStr(*oft._ptr, _ptr);
    }
}
