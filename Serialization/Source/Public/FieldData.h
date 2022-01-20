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

    template<typename TType>
    FieldData<TType>& As();

    virtual size_t& PutData(uint8_t* into, size_t& currentSize) const { };
    virtual size_t& PeekData(uint8_t* from, size_t& currentSize) { };
};

template<typename TType>
struct FieldData : public BaseFieldData
{
private:
	TType* _ptr;
    size_t _typeSize;
    string _name;

public:
    FieldData(TType* ptr, const char* name);
    ~FieldData() override = default;

    const char* GetName() const;
    TType GetValue() const;
    void SetValue(TType newValue) const;
    size_t GetSize() const;

    size_t& PutData(uint8_t* into, size_t& currentSize) const override;
    size_t& PeekData(uint8_t* from, size_t& currentSize) override;
};
