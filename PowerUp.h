#ifndef POWER_UP_H
#define POWER_UP_H

#include "Vertex.h"
#include <string>
#include <unordered_map>

// No need for this to be inside the class - scoped enum is much better and can be forward-declared if necessary.
enum class PowerUpType : uint32_t
{
	WEAPON,
	ARMOUR,
	HEALTH
};

class PowerUp
{
public:
    PowerUp(const char* name, Vertex position, PowerUpType powerUpType)
	: mName(name)
    , mPosition(position)
	, mType(powerUpType)
    {}

	virtual ~PowerUp() = default;

    [[nodiscard]] PowerUpType GetPowerUpType() const
    {
        return mType;
    };

	[[nodiscard]] const Vertex& GetPosition() const
    {
        return mPosition;
    }

protected:
	std::string mName;
    Vertex      mPosition;
    PowerUpType mType;
};

#endif // POWER_UP_H
