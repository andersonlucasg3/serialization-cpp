#include "ByteArray.h"

#include <string>
#include <map>

typedef std::map<uint8_t*, uint32_t> ReferenceMap;

ReferenceMap _referenceCounts;

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

void Retain(uint8_t* buffer)
{
    if (buffer == nullptr) return;
    
    const ReferenceMap::iterator& pair = _referenceCounts.find(buffer);
    
    if (pair == _referenceCounts.end())
    {
        _referenceCounts.insert(std::pair(buffer, 1));
        
        return;
    }
    
    ++ pair->second;
}

void Release(uint8_t** buffer)
{
    if (*buffer == nullptr) return;
    
    const ReferenceMap::iterator& pair = _referenceCounts.find(*buffer);
    
    if (pair == _referenceCounts.end()) return;
    
    if (--pair->second > 0) return;
    
    _referenceCounts.erase(pair);
    
    delete[] *buffer;
    
    *buffer = nullptr;
}

void ByteArray::StoreBuffer(uint8_t* buffer, size_t len, bool copyBuffer)
{
    if (copyBuffer)
    {
        CopyByteArray(buffer, &_buffer, len);
    }
    else
    {
        _buffer = buffer;
    }
    
    _length = len;
    
    Retain(_buffer);
}

ByteArray::ByteArray()
{
    _buffer = nullptr;
    _length = 0;
}

ByteArray::ByteArray(uint8_t* buffer, size_t len, bool copyBuffer)
{
    StoreBuffer(buffer, len, copyBuffer);
}

ByteArray::~ByteArray()
{
    Release(&_buffer);
}

void ByteArray::Set(uint8_t* buffer, size_t len, bool copyBuffer)
{
    if (len > 0 && buffer == nullptr)
    {
        throw "nullptr buffer with len";
    }
    
    Release(&_buffer);
    
    if (buffer == nullptr) return;
    
    StoreBuffer(buffer, len, copyBuffer);
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
    Release(&_buffer);
    
    if (other._buffer == nullptr) return;
    
    StoreBuffer(other._buffer, other._length, false);
    
    return *this;
}

bool ByteArray::operator==(const ByteArray& other) const
{
    if (_length != other._length) return false;
    if (_buffer != other._buffer) return false;
    return true;
}
