#ifndef ARMOUR_H
#define ARMOUR_H

#include "PowerUp.h"

#include <stddef.h>
#include <string.h>

class Armor : public PowerUp
{
public:
    Armor(const char* name, const Vertex& position) :
        PowerUp(name, position)
    {
        mType = ARMOUR;
        mClanTag = NULL;
    }

    ~Armor()
    {
        delete mClanTag;
    }

    const char* GetClanTag() const
    {
        return(mClanTag);
    }

    void SetClanTag(char* n)
    {
        delete mClanTag;
        mClanTag = new char[strlen(n)];
        strcpy(mClanTag, n);
    }

protected:
    char* mClanTag;
};

#endif // ARMOUR_H

