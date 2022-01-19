#include "Serializable.h"

Serializable::Serializable()
{
    _reflectedMembers = list<BaseFieldData*>();
}

Serializable::~Serializable()
{
    for (BaseFieldData* element : _reflectedMembers)
    {
        delete element;
    }
    
    _reflectedMembers.clear();
}

uint8_t *Serializable::Serialize() const
{
    return nullptr;
}











