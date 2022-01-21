#pragma once

#include <list>
#include <string>

using namespace std;

template<typename TType>
struct FieldData;

struct BaseFieldData
{
public:
    virtual ~BaseFieldData() = default;

    virtual size_t GetSize() = 0;
    virtual size_t& PutData(uint8_t* into, size_t& currentSize) const = 0;
    virtual size_t& PeekData(uint8_t* from, size_t& currentSize) = 0;
    virtual void CopyFrom(const BaseFieldData& other) = 0;
    
    BaseFieldData& operator=(const BaseFieldData& other);
};

template<typename TType>
struct FieldData : public BaseFieldData
{
private:
	TType* _ptr;
    size_t _typeSize;
    const char* _name;
    
    void CopyCStr(const char* input, const char** output);
    void FreeCStr(const char** input);
    void CalculateValueSize();
    size_t& PutDataString(const char* _ptr, size_t typeSize, size_t& currentSize, uint8_t* into) const;
    size_t& PeekDataString(const char**_ptr, size_t& currentSize, uint8_t* from);

public:
    static FieldData<TType>& From(BaseFieldData& other);
    static FieldData<TType>* From(BaseFieldData* other);
    
    FieldData(const char* name);
    ~FieldData() override;

    const char* GetName() const;
    TType GetValue() const;
    void SetValue(TType newValue);
    size_t GetSize() override;

    size_t& PutData(uint8_t* into, size_t& currentSize) const override;
    size_t& PeekData(uint8_t* from, size_t& currentSize) override;
    void CopyFrom(const BaseFieldData& other) override;

    FieldData<TType>& operator=(const FieldData<TType>& other);
};
