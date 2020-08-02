#pragma once

//collision class that will keep track of all collisions that happen in a frame

struct collisioninfo
{
	unsigned long ID1;
	unsigned long ID2;

	glm::vec3 projectionaxis;
	float overlap;

	bool ID1move;
};

class collison
{
private:
	std::vector<collisioninfo> normalcollion;

public:

	void addcol(collisioninfo newcol)
	{
		normalcollion.push_back(newcol);
	}
		
	std::vector<collisioninfo> returncol()
	{
		return normalcollion;
	}
	void clearall()
	{
		normalcollion.clear();
	}

};