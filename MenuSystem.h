#pragma once

#include "System.h"
#include <vector>
#include "collisionFunction.h"
#include "menutrans.h"

class menuSystem : public ACC::System //gui system to deal with scene transitions
{

private:

	std::vector<std::shared_ptr<ACC::entity>> menuclicks; 
	std::shared_ptr<menutrans> menchange;

public:

	menuSystem(std::shared_ptr<world> w, std::shared_ptr<menutrans> menuchange);

	void soiwant(std::vector<std::shared_ptr<ACC::entity>> ent);

	void update(float &dt, bool &go);

	std::string returnname()
	{
		return my_System_Name;
	}

	void doihave(std::vector<std::shared_ptr<ACC::entity>> ent);

};