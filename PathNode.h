#ifndef PATH_NODE_H
#define PATH_NODE_H

#include "Vertex.h"

#include <vector>
#include <algorithm>
#include <memory>
#include <string>

class PathNode;
using PathNodePtr = std::unique_ptr<PathNode>;

class PowerUp;
using PowerUptr = std::unique_ptr<PowerUp>;

// These two manage the actual nodes and links, i.e. serve as a storage.
// The ownership semantic is unique - no one should acquire these objects
// in a persistent manner.
using PathNodes = std::vector<PathNodePtr>;
using PowerUps = std::vector<PowerUptr>;

using PathNodeRefs = std::vector<PathNode *>;
using PowerUpRefs = std::vector<PowerUp *>;

class PathNode
{
public:
    PathNode(const char* name, Vertex position);
    ~PathNode();

    void AddLink(PathNode *pathNode);
    void RemoveLink(PathNode *pathNode);
    void AddPowerUp(PowerUp *powerUp);
    void RemovePowerUp(PowerUp *powerUp);

    [[nodiscard]] const char* GetName() const
    {
        return mName.c_str();
    }

	[[nodiscard]] const PathNodeRefs& GetLinks() const
    {
        return mLinks;
    }

	[[nodiscard]] const PowerUpRefs& GetPowerUps() const
    {
        return mPowerUps;
    }

protected:
    Vertex       mPosition;
    std::string  mName;
	PathNodeRefs mLinks;
	PowerUpRefs  mPowerUps;
};

// For this example, all links are symmetric.
inline void LinkNodes(PathNode *n1, PathNode *n2)
{
	n1->AddLink(n2);
	n2->AddLink(n1);
}

// A proxy for linking uptrs instead of plain pointers.
// LinkNodes() was supposed to stay the same, but no one told anything about overloading it :)
inline void LinkNodes(PathNodePtr &n1, PathNodePtr &n2)
{
	n1->AddLink(n2.get());
	n2->AddLink(n1.get());
}

#endif // PATH_NODE_H
