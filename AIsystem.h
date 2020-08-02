#pragma once

#include "System.h"
#include <vector>

class AIsystem : public ACC::System //system that controls all the ai entities
{

private:

	std::vector<std::shared_ptr<ACC::entity>> AIs;
	std::shared_ptr<ACC::entity> player;

public:

	AIsystem(std::shared_ptr<world> w);

	void soiwant(std::vector<std::shared_ptr<ACC::entity>> ent);

	void update(float &dt, bool &go);

	std::string returnname()
	{
		return my_System_Name;
	}

	void doihave(std::vector<std::shared_ptr<ACC::entity>> ent);

};