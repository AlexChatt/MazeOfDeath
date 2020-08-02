#pragma once

#include "Tile.h"
#include <vector>
#include <stdlib.h>   
#include <queue>
#include <memory>

//a class for our tile based map for our game 

class TileMap
{
private:
	std::vector<std::vector<Tile>> tilemap;
	int width;
	int height;
	int obsticalammount;

	std::vector<int> randomtiles;
	int listnum;

	std::vector<int> gettilestoobs(int max, int seed);

public:

	TileMap();

	void setup(int w, int h, int seed);

	void setobsize(int num)
	{
		obsticalammount = num;
	}

	int retwidth()
	{
		return width;
	}
	int retheight()
	{
		return height;
	}

	void createmap();

	bool canaccess(std::vector<std::vector<bool>> obs, int currentobscount);

	std::vector<std::vector<Tile>> returntilemap()
	{
		return tilemap;
	}

	int gettile();


};