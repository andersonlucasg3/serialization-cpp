#pragma once

#include <stdint.h>
#include <cstring>

struct ByteArray
{
private:
    uint8_t* _buffer;
    size_t _length;
    
public:
    ByteArray();
    ByteArray(uint8_t* buffer, size_t len);
    ~ByteArray();
    
    void Set(uint8_t* buffer, size_t len);
    
    const uint8_t* GetBuffer() const;
    const size_t Length() const;
    
    ByteArray& operator=(ByteArray& other);
    bool operator==(const ByteArray& other) const;
};
