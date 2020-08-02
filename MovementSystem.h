#pragma once

#include "System.h"
#include <vector>


class MovementSystem : public ACC::System //deals with the movement of all entities
{

private:

	std::vector<std::shared_ptr<ACC::entity>> moveingents;


public:

	MovementSystem(std::shared_ptr<world> w);

	void soiwant(std::vector<std::shared_ptr<ACC::entity>> ent);

	void update(float &dt, bool &go);

	std::string returnname()
	{
		return my_System_Name;
	}

	void doihave(std::vector<std::shared_ptr<ACC::entity>> ent);

};