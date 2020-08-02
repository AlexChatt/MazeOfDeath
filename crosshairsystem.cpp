#include "crosshairsystem.h"
#include "collisionFunction.h"

crosshairsystem::crosshairsystem(std::shared_ptr<world> w) : System(w)
{
	my_System_Name = "CrosshairSystem";
}

void crosshairsystem::soiwant(std::vector<std::shared_ptr<ACC::entity>> ent)
{
	if (player != NULL && crosshair != NULL)
	{
		return;
	}

	for (int i = 0; i < ent.size(); i++)
	{
		if (ent[i]->doihave(playercomp::TypeID))
		{
			player = ent[i];
		}
		else if (ent[i]->doihave(crosshaircomp::TypeID))
		{
			crosshair = ent[i];
		}

		
	}


}

void crosshairsystem::update(float & dt, bool & go) //update our crosshair position and the players rotation 
{
	if (player != NULL && crosshair != NULL)
	{
		GLint dimentions[4];
		glGetIntegerv(GL_VIEWPORT, dimentions);

		glm::vec3 ray;
		ray.x = (2.0f * inputlogger::instance().getmousex()) / dimentions[2] - 1.0f;
		ray.y = 1.0f - (2.0f * inputlogger::instance().getmousey()) / dimentions[3];
		ray.z = 1.0f;

		glm::vec4 fourdray = glm::vec4(ray.x, ray.y, -1.0, 1.0);

		glm::vec4 eyeray = glm::inverse(myworld->getmaincam()->getproj()) * fourdray;

		eyeray = glm::vec4(eyeray.x, eyeray.y, -1.0, 0.0);

		glm::vec3 raydir = glm::vec3((glm::inverse(myworld->getmaincam()->getview()) * eyeray));

		raydir = glm::normalize(raydir);

		glm::vec3 raypos = myworld->getmaincam()->getpos();

		glm::vec3 mousetoworld = rayplanecollionvec(raypos, raydir, glm::vec3(200, 0, 200), glm::vec3(-200, -1, -200));

		std::shared_ptr<transposecomponent> crosstrans = crosshair->getcomponent<transposecomponent>();
		std::shared_ptr<transposecomponent> playertrans = player->getcomponent<transposecomponent>();
			
		crosstrans->position = mousetoworld;

		glm::vec3 tolookat = playertrans->position + glm::normalize(playertrans->position - crosstrans->position);
		tolookat.y = 0;

		glm::quat playerotate = glm::toQuat(glm::transpose(glm::lookAt(playertrans->position, glm::vec3(tolookat.x,playertrans->position.y, tolookat.z), glm::vec3(0, 1, 0))));
		playertrans->myquat = playerotate;

	}


}

void crosshairsystem::doihave(std::vector<std::shared_ptr<ACC::entity>> ent)
{
	std::vector<std::shared_ptr<ACC::entity>> ents = ent;

	for (int i = 0; i < ents.size(); i++)
	{
		if (ents[i] == player)
		{
			player = NULL;
		}
		else if (ents[i] == crosshair)
		{
			crosshair = NULL;
		}
	}

}

