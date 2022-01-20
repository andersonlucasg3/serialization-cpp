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

    virtual size_t& PutData(uint8_t* into, size_t& currentSize) const = 0;
    virtual size_t& PeekData(uint8_t* from, size_t& currentSize) const = 0;
    virtual void CopyFrom(const BaseFieldData& other) = 0;
    
    BaseFieldData& operator=(const BaseFieldData& other);
};

template<typename TType>
struct FieldData : public BaseFieldData
{
private:
	TType* _ptr;
    size_t _typeSize;
    string _name;

public:
    static FieldData<TType>& From(BaseFieldData& other);
    static FieldData<TType>* From(BaseFieldData* other);
    
    FieldData(TType* ptr, const char* name);
    ~FieldData() override = default;

    const char* GetName() const;
    TType GetValue() const;
    void SetValue(TType newValue) const;
    size_t GetSize() const;

    size_t& PutData(uint8_t* into, size_t& currentSize) const override;
    size_t& PeekData(uint8_t* from, size_t& currentSize) const override;
    void CopyFrom(const BaseFieldData& other) override;

    FieldData<TType>& operator=(const FieldData<TType>& other);
};
