#ifndef POWER_UP_H
#define POWER_UP_H

#include "Vertex.h"
#include <string.h>

class PowerUp
{
public:
    PowerUp(const char* name, Vertex position)
    {
        mPosition = position;
        mName = new char [strlen(name)];
        strcpy(mName, name);
    }

    ~PowerUp()
    {
        delete mName;
    }

    enum PowerUpType
    {
        WEAPON,
        ARMOUR, 
        HEALTH
    };

    PowerUpType GetPowerUpType() const
    {
        return(mType);
    };

    const Vertex& GetPosition() const
    {
        return(mPosition);
    }

protected:
    Vertex      mPosition;
    PowerUpType mType;
    char*       mName;
};

#endif // POWER_UP_H
