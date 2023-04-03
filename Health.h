#ifndef HEALTH_H
#define HEALTH_H

#include "PowerUp.h"

class Health : public PowerUp
{
public:
    Health(const char* name, Vertex position) :
        PowerUp(name, position)
    {
        mType = HEALTH;
    }
    
protected:
    float healing;
};

#endif // HEALTH_H

