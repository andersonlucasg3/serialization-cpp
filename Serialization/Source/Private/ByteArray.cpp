#include "ByteArray.h"

#include <string>

void CopyByteArray(uint8_t* input, uint8_t** output, size_t len)
{
    *output = new uint8_t[len];
    memcpy(*output, input, len);
}

void FreeByteArray(uint8_t** input)
{
    if (*input == nullptr) return;
    
    delete[] *input;
    
    *input = nullptr;
}

ByteArray::ByteArray()
{
    _buffer = nullptr;
    _length = 0;
}

ByteArray::ByteArray(uint8_t* buffer, size_t len)
{
    CopyByteArray(buffer, &_buffer, len);
    _length = len;
}

ByteArray::~ByteArray()
{
    FreeByteArray(&_buffer);
}

void ByteArray::Set(uint8_t* buffer, size_t len)
{
    if (len > 0 && buffer == nullptr)
    {
        throw "nullptr buffer with len";
    }
    
    FreeByteArray(&_buffer);
    
    if (buffer == nullptr) return;
    
    CopyByteArray(buffer, &_buffer, len);
    _length = len;
}

const uint8_t* ByteArray::GetBuffer() const
{
    return _buffer;
}

const size_t ByteArray::Length() const
{
    return _length;
}

ByteArray& ByteArray::operator=(ByteArray& other)
{
    FreeByteArray(&_buffer);
    
    if (other._buffer == nullptr) return;
    
    CopyByteArray(other._buffer, &_buffer, other._length);
    
    return *this;
}

bool ByteArray::operator==(const ByteArray& other) const
{
    if (_length != other._length) return false;
    if (_buffer != other._buffer) return false;
    return true;
}
