#ifndef WEAPON_H
#define WEAPON_H

#include "PowerUp.h"

class Weapon : public PowerUp
{
public:
    Weapon(const char* name, Vertex position) :
        PowerUp(name, position)
    {
        mType = WEAPON;
    }
};

#endif // WEAPON_H

