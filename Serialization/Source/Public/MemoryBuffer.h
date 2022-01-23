#pragma once

#include <stdint.h>
#include <cstring>
#include <map>

struct BaseBuffer
{
public:
    virtual void Set(uint8_t* buffer, size_t len, bool copyBuffer = true) = 0;
    virtual const uint8_t* GetBuffer() const = 0;
    virtual const size_t Length() const = 0;
};

template<typename TBufferType>
struct MemoryBuffer : public BaseBuffer
{
    typedef std::map<TBufferType*, uint32_t> ReferenceMap;
    
private:
    static ReferenceMap _referenceCounts;
    
    TBufferType* _buffer;
    size_t _lengthForBuffer;
    size_t _lengthInBytes;
    
    void Retain();
    void Release();
    void StoreBuffer(TBufferType* buffer, size_t len, bool copyBuffer);
    
public:
    MemoryBuffer();
    MemoryBuffer(MemoryBuffer& other);
    MemoryBuffer(TBufferType* buffer, size_t len, bool copyBuffer = true);
    ~MemoryBuffer();
    
    template<typename TDataType = TBufferType>
    void Set(std::enable_if_t<std::is_same_v<TDataType, TBufferType>>* buffer, size_t len, bool copyBuffer = true);
    
    template<typename TDataType = TBufferType>
    const std::enable_if_t<std::is_same_v<TDataType, TBufferType>>* GetBuffer() const;
    
    void Set(uint8_t* buffer, size_t len, bool copyBuffer = true) override;
    const uint8_t* GetBuffer() const override;
    const size_t Length() const override;
    
    template<typename TDataType>
    const size_t Length() const;
    
    MemoryBuffer& operator=(MemoryBuffer& other);
    bool operator==(const MemoryBuffer& other) const;
};
