#pragma once

#include "PathfinidngTile.h"
#include <vector>
#include <memory>
#include <glm.hpp>
#include "Tile.h"

//our class that will allow for a star pathfinding

class pathfinding
{

private:
	std::vector<std::vector<std::shared_ptr<pathfindingTile>>> tilemap;

	std::vector<std::shared_ptr<pathfindingTile>> openlist;
	std::vector<std::shared_ptr<pathfindingTile>> closedlist;
	std::vector<std::shared_ptr<pathfindingTile>> pathcalculated;
	std::vector<glm::vec3> pathcoods;

	int tilemapwitdh;
	int tilemapheight;
	int mapmaxsize;

	void connectionsetup();
	bool outofbounds(int x, int z);
public:

	pathfinding();
	void createpathmap(std::vector<std::vector<Tile>> gamemap, int mapwidth, int mapheight);
	void findpath(std::shared_ptr<pathfindingTile> ontile, std::shared_ptr<pathfindingTile>goal);
	void clear();
	std::vector<glm::vec3> returnpath();
	bool closedlistcheck(std::shared_ptr<pathfindingTile>tiletocheck);
	bool diagwallcheck(std::shared_ptr<pathfindingTile> ontile, std::shared_ptr<pathfindingTile> diagtile);

	std::vector<glm::vec3> getpathto(glm::vec3 target, glm::vec3 mypos);


};