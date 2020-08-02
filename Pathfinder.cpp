#include "Pathfinder.h"

pathfinding::pathfinding()
{


}

void pathfinding::createpathmap(std::vector<std::vector<Tile>> gamemap, int mapwidth, int mapheight) //create our pathfinding tile map 
{
	tilemapwitdh = mapwidth;
	tilemapheight = mapheight;
	tilemap.resize(mapwidth);

	for (int i = 0; i < mapwidth; i++)
	{
		tilemap[i].resize(mapheight);
	}

	for (int i = 0; i < mapwidth; i++)
	{
		for (int j = 0; j < mapheight; j++)
		{
			std::shared_ptr<pathfindingTile> newtile = std::make_shared<pathfindingTile>();
			newtile->pos = gamemap[i][j].position;
			newtile->index = glm::vec2(i, j);
			newtile->accessible = !gamemap[i][j].obstucted;
			tilemap[i][j] = newtile;
		}
	}

	connectionsetup();
}

void pathfinding::findpath(std::shared_ptr<pathfindingTile> ontile, std::shared_ptr<pathfindingTile> goal) //get a path from our current tile to the objective tile 
{
	int f = 100000;
	std::shared_ptr<pathfindingTile> nexttile;
	int p;
	std::vector<std::shared_ptr<pathfindingTile>> cons;
	std::vector<int> contype;
	int costoftype;
	bool diagcheck = true;


	if (ontile == goal)
	{
		std::shared_ptr<pathfindingTile> temp = ontile;
		pathcalculated.push_back(temp);
		while (temp->parenttile != NULL)
		{
			temp = temp->parenttile;
			pathcalculated.push_back(temp);
		}

		int x = pathcalculated.size() - 1;
		pathcalculated.erase(pathcalculated.begin() + x);

		for (int i = pathcalculated.size() - 1; i > -1; i--)
		{
			pathcoods.push_back(pathcalculated[i]->pos);
		}

		return;
	}


	if (closedlist.size() > 1000) // a fail safe incase the worst happens 
	{
		return;
	}

	closedlist.push_back(ontile);

	if (openlist.size() > 0)
	{
		for (int i = 0; i < openlist.size(); i++)
		{
			if (ontile == openlist[i])
			{
				openlist.erase(openlist.begin() + i);
				break;
			}
		}
	}

	cons = ontile->connections;
	contype = ontile->contype;

	for (int i = 0; i < cons.size(); i++)
	{
		diagcheck = true;

		if (!closedlistcheck(cons[i]) && cons[i]->accessible)
		{
			if (contype[i] == 0)
			{
				costoftype = cons[i]->mycost;
			}
			if (contype[i] == 1)
			{
				if (diagwallcheck(ontile, cons[i]))
				{
					costoftype = sqrt(cons[i]->mycost * cons[i]->mycost + cons[i]->mycost * cons[i]->mycost);
				}
				else
				{
					diagcheck = false;
				}
			}

			if (diagcheck == true)
			{
				cons[i]->setup(goal, costoftype, ontile);
				openlist.push_back(cons[i]);
			}
		}
	}

	for (int i = 0; i < openlist.size(); i++)
	{
		if (openlist[i]->F < f)
		{
			f = openlist[i]->F;
			p = i;
			nexttile = openlist[i];
		}
	}

	if (openlist.size() == 0)
	{
		return;
	}
	else
	{
		findpath(nexttile, goal);
	}

	return;

}

void pathfinding::clear() //clean up everything for a new path finding search 
{
	openlist.clear();
	closedlist.clear();
	pathcalculated.clear();
	pathcoods.clear();

	for (int i = 0; i < tilemapwitdh; i++)
	{
		for (int j = 0; j < tilemapheight; j++)
		{
			tilemap[i][j]->reset();
		}
		
	}
}

std::vector<glm::vec3> pathfinding::returnpath()
{
	return pathcoods;
}

bool pathfinding::closedlistcheck(std::shared_ptr<pathfindingTile> tiletocheck)
{
	for (int i = 0; i < closedlist.size(); i++)
	{
		if (tiletocheck == closedlist[i])
		{
			return true;
		}
	}

	return false;
}

bool pathfinding::diagwallcheck(std::shared_ptr<pathfindingTile> ontile, std::shared_ptr<pathfindingTile> diagtile) //make sure our entities does not do any stupid movements 
{
	std::vector<std::shared_ptr<pathfindingTile>> ontilecon = ontile->connections;
	std::vector<std::shared_ptr<pathfindingTile>> diagtilecon = diagtile->connections;

	for (int i = 0; i < ontilecon.size(); i++)
	{
		for (int j = 0; j < diagtilecon.size(); j++)
		{
			if (ontilecon[i] == diagtilecon[j])
			{
				if (ontilecon[i]->accessible == false)
				{
					return false;
				}
			}

		}
	}

	return true;

}

std::vector<glm::vec3> pathfinding::getpathto(glm::vec3 target, glm::vec3 mypos) //set the goal tile and the current standing on tile, then get the path to the target 
{
	glm::vec2 targettileneeded = glm::vec2((std::floor(target.x + 10)), (std::floor(target.z + 10)));
	glm::vec2 mytile = glm::vec2(std::round(mypos.x + 10), std::round(mypos.z + 10));

	if (mytile.x < 0)
	{
		mytile.x = 1;
	}
	if (mytile.y < 0)
	{
		mytile.y = 1;
	 }

	std::shared_ptr<pathfindingTile> mypostile = tilemap[mytile.x][mytile.y];
	std::shared_ptr<pathfindingTile> targettile = tilemap[targettileneeded.x][targettileneeded.y];

	findpath(mypostile, targettile);

	if (pathcoods.size() != 0)
	{
		pathcoods.push_back(target);
	}


	return pathcoods;
}

void pathfinding::connectionsetup() //setup all of our tile connections 
{
	for (int i = 0; i < tilemapwitdh; i++)
	{
		for (int j = 0; j < tilemapheight; j++)
		{
			if (!outofbounds(i - 1, j))
			{
				tilemap[i][j]->setconnection(tilemap[i - 1][j], 0);
			}
			if (!outofbounds(i + 1, j))
			{
				tilemap[i][j]->setconnection(tilemap[i + 1][j], 0);
			}
			if (!outofbounds(i, j - 1))
			{
				tilemap[i][j]->setconnection(tilemap[i][j - 1], 0);
			}
			if (!outofbounds(i, j + 1))
			{
				tilemap[i][j]->setconnection(tilemap[i][j + 1], 0);
			}
			if (!outofbounds(i - 1, j - 1))
			{
				tilemap[i][j]->setconnection(tilemap[i - 1][j - 1], 1);
			}
			if (!outofbounds(i + 1, j + 1))
			{
				tilemap[i][j]->setconnection(tilemap[i + 1][j + 1], 1);
			}
			if (!outofbounds(i + 1, j - 1))
			{
				tilemap[i][j]->setconnection(tilemap[i + 1][j - 1], 1);
			}
			if (!outofbounds(i - 1, j + 1))
			{
				tilemap[i][j]->setconnection(tilemap[i - 1][j + 1], 1);
			}
		}
	}

}

bool pathfinding::outofbounds(int x, int z) //out of tilemap check 
{
	if (x >= tilemapwitdh || x < 0)
	{
		return true;
	}
	if (z >= tilemapheight || z < 0)
	{
		return true;
	}

	return false;


}