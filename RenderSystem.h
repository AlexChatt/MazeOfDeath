#pragma once

#include "System.h"
#include <vector>


class RenderSystem : public ACC::System //deals with the rendering of entities 
{

private:

	std::vector<std::shared_ptr<ACC::entity>> modelents;
	std::vector<std::shared_ptr<ACC::entity>> backdraw;
	std::vector<std::shared_ptr<ACC::entity>> lights;


public:

	RenderSystem(std::shared_ptr<world> w);

	void soiwant(std::vector<std::shared_ptr<ACC::entity>> ent);

	void update(float &dt, bool &go);

	std::string returnname()
	{
		return my_System_Name;
	}

	void doihave(std::vector<std::shared_ptr<ACC::entity>> ent);

};