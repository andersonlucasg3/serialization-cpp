#pragma once

#include <list>
#include <string>

using namespace std;

template<typename TType>
struct FieldData;

struct BaseFieldData
{
public:
    template<typename TType>
    FieldData<TType>& As();
};

template<typename TType>
struct FieldData : public BaseFieldData
{
private:
	TType* _ptr;
    string _name;

public:
    FieldData(TType* ptr, const char* name);
    const char* GetName() const;
    TType GetValue() const;
    void SetValue(TType newValue) const;
};