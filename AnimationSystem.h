#pragma once

#include "System.h"
#include <vector>


class animationsystem : public ACC::System //system that contoles any entity that is based on another
{

private:

	std::vector<std::shared_ptr<ACC::entity>> connectedents;


public:

	animationsystem(std::shared_ptr<world> w);

	void soiwant(std::vector<std::shared_ptr<ACC::entity>> ent);

	void update(float &dt, bool &go);

	std::string returnname()
	{
		return my_System_Name;
	}

	void doihave(std::vector<std::shared_ptr<ACC::entity>> ent);

};