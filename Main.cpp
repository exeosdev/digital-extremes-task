#include "PathNode.h"
#include "PowerUp.h"
#include "Weapon.h"
#include "Health.h"
#include "Armor.h"
#include <cstdio>

// Not sure about these statics (i.e. whether that's an intention or should be classified as a wrong design).
// Let's assume we have a global "library" of Power Ups in the world and all paths for a map stored here, accessible
// from various parts of the game logic. That (kinda) justifies this approach. We'll proceed assuming it's okay.
// A note: since we stick to the idea of having these as static globals, we have a guarantee that the destruction will
// happen after main() quits - so there is no way (detached threads aside) to access a deleted node/power-up.
static PathNodes sPathNodes;
static PowerUps sPowerUps;

bool FindPowerUp(PathNodes& path, PowerUpType mType, PathNode *start)
{
    /* Example:
    path.push_back(start);
    path.push_back(secondNode);
    path.push_back(endNode);
    return(true);
    */
    
    return(false); // No path found.
}

int main(int, char*[])
{
    sPathNodes.emplace_back(new PathNode("Node0", Vertex(300, 60, 0)));
    sPathNodes.emplace_back(new PathNode("Node1", Vertex(100, 60, 0)));
    sPathNodes.emplace_back(new PathNode("Node2", Vertex(80, 560, 0)));
    sPathNodes.emplace_back(new PathNode("Node3", Vertex(280, 650, 0)));
    sPathNodes.emplace_back(new PathNode("Node4", Vertex(300, 250, 0)));
    sPathNodes.emplace_back(new PathNode("Node5", Vertex(450, 400, 0)));
    sPathNodes.emplace_back(new PathNode("Node6", Vertex(450, 60, 0)));
    sPathNodes.emplace_back(new PathNode("Node7", Vertex(450, 400, 0)));

    LinkNodes(sPathNodes[1], sPathNodes[4]);
    LinkNodes(sPathNodes[0], sPathNodes[1]);
    LinkNodes(sPathNodes[0], sPathNodes[6]);
    LinkNodes(sPathNodes[0], sPathNodes[4]);
    LinkNodes(sPathNodes[7], sPathNodes[4]);
    LinkNodes(sPathNodes[7], sPathNodes[5]);
    LinkNodes(sPathNodes[2], sPathNodes[4]);
    LinkNodes(sPathNodes[2], sPathNodes[3]);
    LinkNodes(sPathNodes[3], sPathNodes[5]);

    sPowerUps.emplace_back(new Weapon("Weapon0", Vertex(340, 670, 0)));
    sPathNodes[3]->AddPowerUp(sPowerUps[0]);    
    sPowerUps.emplace_back(new Weapon("Weapon1", Vertex(500, 220, 0)));
    sPathNodes[7]->AddPowerUp(sPowerUps[1]);    

    sPowerUps.emplace_back(new Health("Health0", Vertex(490, 10, 0)));
    sPathNodes[6]->AddPowerUp(sPowerUps[2]);    
    sPowerUps.emplace_back(new Health("Health1", Vertex(120, 20, 0)));
    sPathNodes[1]->AddPowerUp(sPowerUps[3]);    

    sPowerUps.emplace_back(new Armor("Armour0", Vertex(500, 360, 0)));
    sPathNodes[5]->AddPowerUp(sPowerUps[4]);    
    sPowerUps.emplace_back(new Armor("Armour1", Vertex(180, 525, 0)));
    sPathNodes[2]->AddPowerUp(sPowerUps[5]);    

    PathNodes path;

    if(!FindPowerUp(path, PowerUp::WEAPON, sPathNodes[4]))
    {
        printf("No path found: IMPOSSIBLE!\n");
    }
    else
    {
        printf("Path found: ");

        for(PathNodes::iterator i = path.begin(); i != path.end(); ++i)
        {
            PathNode *n = *i;
            printf("%s ", n->GetName());
        }

        printf("\n");
    }
       
    return(0);
}
