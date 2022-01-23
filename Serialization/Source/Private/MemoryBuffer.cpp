#include "MemoryBuffer.h"

#include <string>

template<typename TBufferType>
typename MemoryBuffer<TBufferType>::ReferenceMap MemoryBuffer<TBufferType>::_referenceCounts;

template<typename TBufferType>
void CopyByteArray(TBufferType* input, TBufferType** output, size_t len)
{
    *output = new TBufferType[len];
    memcpy(*output, input, len);
}

template<typename TBufferType>
void FreeByteArray(TBufferType** input)
{
    if (*input == nullptr) return;
    
    delete[] *input;
    
    *input = nullptr;
}

template<typename TBufferType>
void MemoryBuffer<TBufferType>::Retain()
{
    if (_buffer == nullptr) return;
    
    const typename ReferenceMap::iterator& pair = _referenceCounts.find(_buffer);
    
    if (pair == _referenceCounts.end())
    {
        _referenceCounts.insert(std::pair(_buffer, 1));
        
        return;
    }
    
    ++ pair->second;
}

template<typename TBufferType>
void MemoryBuffer<TBufferType>::Release()
{
    if (_buffer == nullptr) return;
    
    const typename ReferenceMap::iterator& pair = _referenceCounts.find(_buffer);
    
    if (pair == _referenceCounts.end()) return;
    
    if (--pair->second > 0) return;
    
    _referenceCounts.erase(pair);
    
    delete[] _buffer;
    
    _buffer = nullptr;
    
    _lengthInBytes = 0;
    _lengthForBuffer = 0;
}

template<typename TBufferType>
void MemoryBuffer<TBufferType>::StoreBuffer(TBufferType* buffer, size_t len, bool copyBuffer)
{
    if (copyBuffer)
    {
        CopyByteArray(buffer, &_buffer, len);
    }
    else
    {
        _buffer = buffer;
    }
    
    _lengthForBuffer = len;
    _lengthInBytes = len * sizeof(TBufferType);
    
    Retain();
}

template<typename TBufferType>
MemoryBuffer<TBufferType>::MemoryBuffer()
{
    _buffer = nullptr;
    _lengthInBytes = 0;
    _lengthForBuffer = 0;
}

template<typename TBufferType>
MemoryBuffer<TBufferType>::MemoryBuffer(MemoryBuffer& other)
{
    StoreBuffer(other._buffer, other._lengthForBuffer, false);
}

template<typename TBufferType>
MemoryBuffer<TBufferType>::MemoryBuffer(TBufferType* buffer, size_t len, bool copyBuffer)
{
    StoreBuffer(buffer, len, copyBuffer);
}

template<typename TBufferType>
MemoryBuffer<TBufferType>::~MemoryBuffer()
{
    Release();
}

template<typename TBufferType>
template<typename TDataType>
void MemoryBuffer<TBufferType>::Set(std::enable_if_t<std::is_same_v<TDataType, TBufferType>>* buffer, size_t len, bool copyBuffer)
{
    if (len > 0 && buffer == nullptr)
    {
        throw "nullptr buffer with len";
    }
    
    Release();
    
    if (buffer == nullptr) return;
    
    StoreBuffer((TBufferType*)buffer, len, copyBuffer);
}

template<typename TBufferType>
void MemoryBuffer<TBufferType>::Set(uint8_t* buffer, size_t len, bool copyBuffer)
{
    Set<TBufferType>((TBufferType*)buffer, len, copyBuffer);
}

template<typename TBufferType>
template<typename TDataType>
const std::enable_if_t<std::is_same_v<TDataType, TBufferType>>* MemoryBuffer<TBufferType>::GetBuffer() const
{
    return _buffer;
}

template<typename TBufferType>
const uint8_t* MemoryBuffer<TBufferType>::GetBuffer() const
{
    return (uint8_t*)_buffer;
}

template<typename TBufferType>
const size_t MemoryBuffer<TBufferType>::Length() const
{
    return _lengthInBytes;
}

template<typename TBufferType>
template<typename TDataType>
const size_t MemoryBuffer<TBufferType>::Length() const
{
    return _lengthInBytes / sizeof(TDataType);
}

template<typename TBufferType>
MemoryBuffer<TBufferType>& MemoryBuffer<TBufferType>::operator=(MemoryBuffer<TBufferType>& other)
{
    Release();
    
    if (other._buffer != nullptr)
    {
        StoreBuffer(other._buffer, other._lengthForBuffer, false);
    }
    
    return *this;
}

template<typename TBufferType>
bool MemoryBuffer<TBufferType>::operator==(const MemoryBuffer<TBufferType>& other) const
{
    if (_lengthInBytes != other._lengthInBytes) return false;
    if (_buffer != other._buffer) return false;
    return true;
}

#define INSTANTIATE_ALL(type) \
template struct MemoryBuffer<type>;

#include "TemplateInstantiation.hpp"
