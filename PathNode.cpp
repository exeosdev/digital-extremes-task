
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

bool PathNode::HasPowerUp(PowerUpType puType) const
{
	for(auto *powerUp : mPowerUps)
	{
		if(powerUp->GetPowerUpType() == puType)
		{
			return true;
		}
	}
	return false;
}


void FindPowerUp(PowerUpType puType, PathState &pathState, PathState &currentShortestPath, NodeMarkupTable &nodeMarkupTable)
{
	auto *currentNode = pathState.path.back();
	const auto &currentNodeLinks = currentNode->GetLinks();

	if(currentNodeLinks.empty())
	{
		return;
	}

	for(auto *link : currentNodeLinks)
	{
		if(nodeMarkupTable.count(link) == 0)
		{
			const auto pathLength = length(link->GetPosition() - currentNode->GetPosition());
			pathState.pathLength += pathLength;
			pathState.path.push_back(link);

			if(link->HasPowerUp(puType))
			{
				if((currentShortestPath.pathLength == 0.0f) || (pathState.pathLength < currentShortestPath.pathLength))
				{
					currentShortestPath = pathState;
				}
			}
			else
			{
				nodeMarkupTable.insert(link);
				FindPowerUp(puType, pathState, currentShortestPath, nodeMarkupTable);
				nodeMarkupTable.erase(link);
			}

			pathState.pathLength -= pathLength;
			pathState.path.pop_back();
		}
	}
}

PathNodeRefs FindPowerUp(PowerUpType puType, PathNode *start)
{
	PathState thePath;
	PathState pathState;
	NodeMarkupTable markupTable;

	pathState.path.push_back(start);
	markupTable.insert(start);

	FindPowerUp(puType, pathState, thePath, markupTable);

	return thePath.path;
}
