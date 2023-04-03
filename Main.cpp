#include "PathNode.h"
#include "PowerUp.h"
#include "Weapon.h"
#include "Health.h"
#include "Armor.h"

int main(int, char*[])
{
	{
		PathNodes sPathNodesDefault;
		PowerUps sPowerUpsDefault;

		sPathNodesDefault.emplace_back(new PathNode("Node0", Vertex(300, 60, 0)));
		sPathNodesDefault.emplace_back(new PathNode("Node1", Vertex(100, 60, 0)));
		sPathNodesDefault.emplace_back(new PathNode("Node2", Vertex(80, 560, 0)));
		sPathNodesDefault.emplace_back(new PathNode("Node3", Vertex(280, 650, 0)));
		sPathNodesDefault.emplace_back(new PathNode("Node4", Vertex(300, 250, 0)));
		sPathNodesDefault.emplace_back(new PathNode("Node5", Vertex(450, 400, 0)));
		sPathNodesDefault.emplace_back(new PathNode("Node6", Vertex(450, 60, 0)));
		sPathNodesDefault.emplace_back(new PathNode("Node7", Vertex(450, 400, 0)));

		LinkNodes(sPathNodesDefault[1], sPathNodesDefault[4]);
		LinkNodes(sPathNodesDefault[0], sPathNodesDefault[1]);
		LinkNodes(sPathNodesDefault[0], sPathNodesDefault[6]);
		LinkNodes(sPathNodesDefault[0], sPathNodesDefault[4]);
		LinkNodes(sPathNodesDefault[7], sPathNodesDefault[4]);
		LinkNodes(sPathNodesDefault[7], sPathNodesDefault[5]);
		LinkNodes(sPathNodesDefault[2], sPathNodesDefault[4]);
		LinkNodes(sPathNodesDefault[2], sPathNodesDefault[3]);
		LinkNodes(sPathNodesDefault[3], sPathNodesDefault[5]);

		sPowerUpsDefault.emplace_back(new Weapon("Weapon0", Vertex(340, 670, 0)));
		sPathNodesDefault[3]->AddPowerUp(sPowerUpsDefault[0].get());
		sPowerUpsDefault.emplace_back(new Weapon("Weapon1", Vertex(500, 220, 0)));
		sPathNodesDefault[7]->AddPowerUp(sPowerUpsDefault[1].get());

		sPowerUpsDefault.emplace_back(new Health("Health0", Vertex(490, 10, 0)));
		sPathNodesDefault[6]->AddPowerUp(sPowerUpsDefault[2].get());
		sPowerUpsDefault.emplace_back(new Health("Health1", Vertex(120, 20, 0)));
		sPathNodesDefault[1]->AddPowerUp(sPowerUpsDefault[3].get());

		sPowerUpsDefault.emplace_back(new Armor("Armour0", Vertex(500, 360, 0)));
		sPathNodesDefault[5]->AddPowerUp(sPowerUpsDefault[4].get());
		sPowerUpsDefault.emplace_back(new Armor("Armour1", Vertex(180, 525, 0)));
		sPathNodesDefault[2]->AddPowerUp(sPowerUpsDefault[5].get());

		// The original test
		const auto path = FindPowerUp(PowerUpType::WEAPON, sPathNodesDefault[4].get());
		PrintPath(path, "The Original Example");
	}

	{
		// Single node graph, no PU
		PathNodes sPathNodesSingleNode;
		sPathNodesSingleNode.emplace_back(new PathNode("Node0", Vertex(300, 60, 0)));
		const auto path = FindPowerUp(PowerUpType::WEAPON, sPathNodesSingleNode[0].get());
		PrintPath(path, "Single Node Graph/No PU");
	}

	{
		// Single node graph, with PU
		PathNodes sPathNodesSingleNode2;
		PowerUps sPowerUpsSingleNode2;
		sPathNodesSingleNode2.emplace_back(new PathNode("Node0", Vertex(300, 60, 0)));
		sPowerUpsSingleNode2.emplace_back(new Weapon("Weapon0", Vertex(340, 670, 0)));
		sPathNodesSingleNode2[0]->AddPowerUp(sPowerUpsSingleNode2[0].get());
		const auto path = FindPowerUp(PowerUpType::WEAPON, sPathNodesSingleNode2[0].get());
		PrintPath(path, "Single Node Graph/With PU");
	}

	{
		// Two identical nodes, one with PU
		PathNodes sPathNodesCycle;
		PowerUps sPowerUpsCycle;
		sPathNodesCycle.emplace_back(new PathNode("Node0", Vertex(300, 60, 0)));
		sPathNodesCycle.emplace_back(new PathNode("Node1", Vertex(300, 60, 0)));
		LinkNodes(sPathNodesCycle[0], sPathNodesCycle[1]);
		sPowerUpsCycle.emplace_back(new Weapon("Weapon0", Vertex(340, 670, 0)));
		//sPathNodesCycle[0]->AddPowerUp(sPowerUpsCycle[0].get());
		sPathNodesCycle[1]->AddPowerUp(sPowerUpsCycle[0].get());
		const auto path1 = FindPowerUp(PowerUpType::WEAPON, sPathNodesCycle[0].get());
		PrintPath(path1, "Two Identical/Start on Empty");
		const auto path2 = FindPowerUp(PowerUpType::WEAPON, sPathNodesCycle[1].get());
		PrintPath(path2, "Two Identical/Start on PU");
	}
       
    return 0;
}
