#ifndef PATH_NODE_H
#define PATH_NODE_H

#include "Vertex.h"

#include <vector>
#include <algorithm>
#include <memory>
#include <string>
#include <unordered_set>
#include <limits>


enum class PowerUpType : uint32_t;

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

	[[nodiscard]] bool HasPowerUp(PowerUpType puType) const;

	[[nodiscard]] float GetClosestPowerUpDistanceOfType(PowerUpType puType) const;

    [[nodiscard]] Vertex GetPosition() const
    {
        return mPosition;
    }

    [[nodiscard]] const char* GetName() const
    {
        return mName.c_str();
    }

	// Returns the link with the specified index
	[[nodiscard]] PathNode * GetLink(size_t index) const
    {
        return mLinks[index];
    }

	// Returns true if the specified link index is valid
	[[nodiscard]] bool CheckLinkIndex(size_t index) const
    {
        return index < mLinks.size();
    }

	[[nodiscard]] const PathNodeRefs& GetLinks() const
    {
        return mLinks;
    }

	[[nodiscard]] bool Empty() const
    {
        return mLinks.size() == 1;
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

struct PathInfo
{
	PathNodeRefs pathNodes;
	float pathLength = std::numeric_limits<float>::max();

	explicit operator bool() const noexcept
	{
		return !pathNodes.empty();
	}
};

using NodeMarkupTable = std::unordered_set<PathNode *>;

PathInfo FindPowerUp(PowerUpType puType, PathNode *start);
void PrintPath(const PathInfo &path, const char *desc = nullptr);

#endif // PATH_NODE_H
