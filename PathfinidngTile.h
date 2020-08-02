#pragma once
#include <glm.hpp>
#include <memory>
#include <vector>

//a pathfinding tile with all of the data we need for A* pathfinding

struct pathfindingTile
{
	glm::vec3 pos;
	glm::vec2 index;

	glm::vec3 centerpos;

	int G;
	int H;
	int F;
	int preG;
	bool accessible;

	std::shared_ptr<pathfindingTile> parenttile;

	std::vector<std::shared_ptr<pathfindingTile>> connections;
	std::vector<int> contype;

	bool targettile;
	bool inopen;
	float mycost;

	pathfindingTile()
	{
		G = 0;
		H = 0;
		F = 0;
		preG = 100000000;
		parenttile = NULL;
		inopen = false;
		mycost = 10;
		accessible = true;
		targettile = false;
	}

	void setup(std::shared_ptr<pathfindingTile> destination, float cost, std::shared_ptr<pathfindingTile> par);

	void setconnection(std::shared_ptr<pathfindingTile> connect, int type);

	void reset()
	{
		G = 0;
		H = 0;
		F = 0;
		preG = 100000000;
		parenttile = NULL;
		targettile = false;
		inopen = false;
	}

};