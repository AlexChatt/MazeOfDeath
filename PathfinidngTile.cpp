#include "PathfinidngTile.h"

void pathfindingTile::setup(std::shared_ptr<pathfindingTile> destination, float cost, std::shared_ptr<pathfindingTile> par)
{
	if (G + cost + par->G <= preG) // if the new G is a bigger cost then dont do the rest 
	{
		G = 0;
		G += cost;

		parenttile = par;
		G += parenttile->G;

		glm::vec2 temp = destination->index;// need to change this into the tile pos by div by tile size

		int xdif = abs(temp.x - index.x);
		int zdif = abs(temp.y - index.y);

		H = (xdif * 10) + (zdif * 10);

		F = G + H;

		preG = G; // used for a star, work out the G,H and F of the tile based on how far we are from the destination and the cost 
	}
}

void pathfindingTile::setconnection(std::shared_ptr<pathfindingTile> connect, int type) //setup our tiles connections 
{
	connections.push_back(connect);
	if (type == 0)
	{
		contype.push_back(0);
	}
	if (type == 1)
	{
		contype.push_back(1);
	}

}
