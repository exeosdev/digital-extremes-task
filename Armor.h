#ifndef ARMOUR_H
#define ARMOUR_H

#include "PowerUp.h"

class Armor : public PowerUp
{
public:
    Armor(const char* name, const Vertex& position)
	: PowerUp(name, position, PowerUpType::ARMOUR)
    {}

    virtual ~Armor() = default;

    [[nodiscard]] const char* GetClanTag() const
    {
        return mClanTag.c_str();
    }

    void SetClanTag(const char* n)
    {
		mClanTag.assign(n ? n : "");
    }

protected:
    std::string mClanTag;
};

#endif // ARMOUR_H

