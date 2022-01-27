#pragma once

#include <map>

struct BaseBuffer
{
public:
    virtual void Set(uint8_t* buffer, size_t len, bool copyBuffer = true) = 0;
    virtual const uint8_t* GetBuffer() const = 0;
    virtual size_t Length() const = 0;
};

template<typename TBufferType>
void CopyByteArray(TBufferType* input, TBufferType** output, size_t len);
template<typename TBufferType>
void FreeByteArray(TBufferType** input);

template<typename TBufferType>
struct MemoryBuffer : public BaseBuffer
{
    typedef std::map<TBufferType*, uint32_t> ReferenceMap;
    
private:
    static ReferenceMap _referenceCounts;
    
    TBufferType* _buffer;
    size_t _lengthForBuffer;
    size_t _lengthInBytes;
    
    void Retain()
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

    void Release()
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

    void StoreBuffer(TBufferType* buffer, size_t len, bool copyBuffer)
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
    
public:
    MemoryBuffer()
    {
        _buffer = nullptr;
        _lengthInBytes = 0;
        _lengthForBuffer = 0;
    }

    MemoryBuffer(MemoryBuffer& other)
    {
        StoreBuffer(other._buffer, other._lengthForBuffer, false);
    }

    MemoryBuffer(TBufferType* buffer, size_t len, bool copyBuffer = true)
    {
        StoreBuffer(buffer, len, copyBuffer);
    }

    ~MemoryBuffer()
    {
        Release();
    }
    
    template<typename TDataType = TBufferType>
    void Set(std::enable_if_t<std::is_same_v<TDataType, TBufferType>>* buffer, size_t len, bool copyBuffer = true)
    {
        if (len > 0 && buffer == nullptr)
        {
            throw "nullptr buffer with len";
        }

        Release();

        if (buffer == nullptr) return;

        StoreBuffer((TBufferType*)buffer, len, copyBuffer);
    }
    
    void Set(uint8_t* buffer, size_t len, bool copyBuffer = true) override
    {
        Set<TBufferType>((TBufferType*)buffer, len, copyBuffer);
    }

    const uint8_t* GetBuffer() const override
    {
        return (uint8_t*)_buffer;
    }

    template<typename TDataType = TBufferType>
    const std::enable_if_t<std::is_same_v<TDataType, TBufferType>>* GetBuffer() const
    {
        return _buffer;
    }

    size_t Length() const override
    {
        return _lengthForBuffer;
    }

    template<typename TDataType>
    size_t Length() const
    {
        return _lengthInBytes / sizeof(TDataType);
    }
    
    MemoryBuffer& operator=(const MemoryBuffer& other)
    {
        Release();

        if (other._buffer != nullptr)
        {
            StoreBuffer(other._buffer, other._lengthForBuffer, false);
        }

        return *this;
    }

    bool operator==(const MemoryBuffer& other) const
    {
        if (_lengthInBytes != other._lengthInBytes) return false;
        if (_buffer != other._buffer) return false;
        return true;
    }
};

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
