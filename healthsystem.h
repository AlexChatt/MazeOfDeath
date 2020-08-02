#pragma once

#include "System.h"
#include "scorekeeper.h"

class healthsystem : public ACC::System //deals with the health of the entities and getting rid of any entity below 0 health
{

private:

	std::vector<std::shared_ptr<ACC::entity>> healthents;
	std::shared_ptr<scorekeeper> myscorekeeper;

public:

	healthsystem(std::shared_ptr<world> w, std::shared_ptr<scorekeeper> sk);

	void soiwant(std::vector<std::shared_ptr<ACC::entity>> ent);

	void update(float &dt, bool &go);

	std::string returnname()
	{
		return my_System_Name;
	}

	void doihave(std::vector<std::shared_ptr<ACC::entity>> ent);

};