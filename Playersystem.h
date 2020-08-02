#pragma once

#include "System.h"
#include <vector>


class Playersystem : public ACC::System //deals with the actions of the player 
{

private:

	std::vector<std::shared_ptr<ACC::entity>> players;


public:

	Playersystem(std::shared_ptr<world> w);

	void soiwant(std::vector<std::shared_ptr<ACC::entity>> ent);

	void update(float &dt, bool &go);

	std::string returnname()
	{
		return my_System_Name;
	}

	void doihave(std::vector<std::shared_ptr<ACC::entity>> ent);

};