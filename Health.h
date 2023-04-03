#ifndef HEALTH_H
#define HEALTH_H

#include "PowerUp.h"

class Health : public PowerUp
{
public:
    Health(const char* name, Vertex position)
	: PowerUp(name, position, PowerUpType::HEALTH)
    {}

	virtual ~Health() = default;

protected:
    float healing = 0.0f;
};

#endif // HEALTH_H

