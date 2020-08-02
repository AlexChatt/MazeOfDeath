#pragma once
#include <glm.hpp> 
#include <memory>
//default tile for our tile map

struct Tile
{
	int x;
	int y;
	glm::vec3 position;
	bool obstucted;

	Tile()
	{
		obstucted = false;
	}

};