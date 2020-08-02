#pragma once

#include "System.h"
#include <gtc/quaternion.hpp>
#include <gtx/quaternion.hpp>

class crosshairsystem : public ACC::System //controls the crosshair and the rotation of the player
{

private:

	std::shared_ptr<ACC::entity> player;
	std::shared_ptr<ACC::entity> crosshair;

public:

	crosshairsystem(std::shared_ptr<world> w);

	void soiwant(std::vector<std::shared_ptr<ACC::entity>> ent);

	void update(float &dt, bool &go);

	std::string returnname()
	{
		return my_System_Name;
	}

	void doihave(std::vector<std::shared_ptr<ACC::entity>> ent);

	glm::vec3 posonmap(glm::vec3 raypos, glm::vec3 raydir);

};