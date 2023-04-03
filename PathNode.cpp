
#include "PathNode.h"
#include "PowerUp.h"

PathNode::PathNode(const char* name, Vertex position)
: mPosition(position)
, mName( name ? name : "" )
{}

PathNode::~PathNode() = default;

void PathNode::AddLink(PathNode *pathNode)
{
	mLinks.emplace_back(pathNode);
}

void PathNode::RemoveLink(PathNode *pathNode)
{
	auto i = std::find( mLinks.begin(), mLinks.end(), pathNode);
	mLinks.erase(i);
}

void PathNode::AddPowerUp(PowerUp *powerUp)
{
	mPowerUps.emplace_back(powerUp);
}

void PathNode::RemovePowerUp(PowerUp *powerUp)
{
	auto i = std::find( mPowerUps.begin(), mPowerUps.end(), powerUp);
	mPowerUps.erase(i);
}
