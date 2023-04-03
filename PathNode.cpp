
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

[[nodiscard]] float PathNode::GetClosestPowerUpDistanceOfType(PowerUpType puType) const
{
	float minDistance = std::numeric_limits<float>::max();
	for(auto *powerUp : mPowerUps)
	{
		if(powerUp->GetPowerUpType() == puType)
		{
			const auto distance = length(powerUp->GetPosition() - GetPosition());
			if(distance < minDistance)
			{
				minDistance = distance;
			}
		}
	}
	return minDistance;
}

using NodeIndices = std::vector<uint32_t>;

void FindPowerUp(
		PowerUpType puType, // The type we are looking for
		PathInfo &pathState, // "Working" path state we operate on
		PathInfo &outputShortestPath, // The Result
		NodeIndices &nodeIndices, // Sub-link indices (see below)
		NodeMarkupTable &nodeMarkupTable // Node markup table
		)
{
	// This function gets initially called with the starting vertex in the currentShortestPath
	// (it is also marked in nodeMarkupTable) and a length = 0;

	while(!pathState.pathNodes.empty())
	{
		// Current node is the last element in the ::pathNodes array
		auto *currentNode = pathState.pathNodes.back();

		if(currentNode->HasPowerUp(puType))
		{
			auto pathLength = pathState.pathLength;

			// I am a bit confused about the fact that positions are also specified for power ups. Does that mean that
			// a power-up is CONNECTED to a node rather than "part of" a node? If so, we should assume there is a distance
			// also between a node and its power up. If that's wrong, disabling this conditional branch changes the behaviour.
			const auto useNodeToPowerUpLocalDistanceToo = true;
			if(useNodeToPowerUpLocalDistanceToo)
			{
				pathLength += currentNode->GetClosestPowerUpDistanceOfType(puType);
			}

			if(pathLength < outputShortestPath.pathLength)
			{
				outputShortestPath.pathNodes = pathState.pathNodes;
				outputShortestPath.pathLength = pathLength;
			}
		}

		// We have our current node, which might or might have not had the requested power-up.
		// Since we are doing DFS, browse through its connected nodes ("children", if you can say that in case of graph..).
		// Take into account the markup table and skip those visited already.
		while(currentNode->CheckLinkIndex(nodeIndices.back()) && (nodeMarkupTable.count(currentNode->GetLink(nodeIndices.back())) != 0))
		{
			++nodeIndices.back();
		}

		// Check if there was a link that we can go to now.
		if(currentNode->CheckLinkIndex(nodeIndices.back()))
		{
			// Fetch the next node/link using the computed index.
			auto *nextNode = currentNode->GetLink(nodeIndices.back());

			// Mark it as visited
			nodeMarkupTable.insert(nextNode);

			// Add it to the "working" path
			pathState.pathNodes.push_back(nextNode);

			// Add the distance to it to the current length.
			pathState.pathLength += length(nextNode->GetPosition() - currentNode->GetPosition());

			// We start iterating through sub-nodes again from zero.
			nodeIndices.push_back(0);

			continue;
		}
		else
		{
			// This is still-but-not-for-too-long current node.
			auto *noLongerCurrentNode = currentNode;

			// Remove/pop it from the state data structures.

			nodeMarkupTable.erase(currentNode);
			pathState.pathNodes.pop_back();
			nodeIndices.pop_back();

			if(!pathState.pathNodes.empty())
			{
				// If there are still nodes in the path, we need to compute back the length and decrease it.
				currentNode = pathState.pathNodes.back();
				pathState.pathLength -= length(noLongerCurrentNode->GetPosition() - currentNode->GetPosition());
				++nodeIndices.back();
			}
		}
	}
}

PathInfo FindPowerUp(PowerUpType puType, PathNode *start)
{
	// All variables are local, no modification is done on the input parameters.
	// Function is fully re-entrant and thread-safe.

	PathInfo thePath;

	PathInfo auxPathInfo;
	auxPathInfo.pathNodes.push_back(start);
	auxPathInfo.pathLength = 0.0f;

	// nodeIndices is a helper for iteration-based implementation. Element at index E represents the current index of a
	// child link (i.e. connected graph node) that should be processed for a pathNodes[E]. When a new node is added to
	// the path, '0' is pushed to the back of this array. Removing an element from pathNodes also pops the last element
	// from nodeIndices.
	NodeIndices nodeIndices;
	nodeIndices.push_back(0);

	// The markup table used to mark which nodes have been visited in a given point of execution.
	NodeMarkupTable markupTable;
	markupTable.insert(start);

	FindPowerUp(puType, auxPathInfo, thePath, nodeIndices, markupTable);

	return thePath;
}

void PrintPath(const PathInfo &path, const char *desc)
{
	if(desc)
	{
		printf("[%s] ", desc);
	}
	if(!path)
	{
		printf("Path is EMPTY (requested path does not exist)\n");
	}
	else
	{
		printf("Path: ");
		for(auto *node : path.pathNodes)
		{
			printf("%s ", node->GetName());
		}
		printf("(length = %f)\n", path.pathLength);
	}
}
