#include "MenuSystem.h"

menuSystem::menuSystem(std::shared_ptr<world> w, std::shared_ptr<menutrans> menuchange) : System(w)
{
	my_System_Name = "menuSystem";
	menchange = menuchange;
}

void menuSystem::soiwant(std::vector<std::shared_ptr<ACC::entity>> ent)
{
	std::vector<unsigned long int> lookfor;
	lookfor.push_back(menucomp::TypeID);
	lookfor.push_back(collisioncomp::TypeID);

	for (int i = 0; i < ent.size(); i++)
	{
		if (ent[i]->doihave(lookfor))
		{
			menuclicks.push_back(ent[i]);
		}
	}

}

void menuSystem::update(float & dt, bool & go)
{
	for (auto menubutton : menuclicks)
	{
		if (inputlogger::instance().getleftmouse())
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

			std::shared_ptr<collisioncomp> entonecol = menubutton->getcomponent<collisioncomp>();

			bool hitbox = rayplanecollion(raypos, raydir, entonecol->myAABB->newmax - glm::vec3(1, 1, 1), entonecol->myAABB->newmin + glm::vec3(1, 1, 1));

			if (hitbox == true)
			{
				std::shared_ptr<menucomp> entonecol = menubutton->getcomponent<menucomp>();
				menchange->change = true;
				if (entonecol->mytype == entonecol->play)
				{
					menchange->changetype = menchange->play;
					return;
				}
				else if (entonecol->mytype == entonecol->quit)
				{
					menchange->changetype = menchange->quit;
					return;
				}
				else if (entonecol->mytype == entonecol->backtomain)
				{
					menchange->changetype = menchange->backtomain;
					return;
				}
			}
		}
	}
}

void menuSystem::doihave(std::vector<std::shared_ptr<ACC::entity>> ent)
{
	std::vector<std::shared_ptr<ACC::entity>> ents = ent;

	for (int i = 0; i < menuclicks.size(); i++)
	{
		for (int j = 0; j < ents.size(); j++)
		{
			if (menuclicks[i] == ents[j])
			{
				menuclicks.erase(menuclicks.begin() + i);
				ents.erase(ents.begin() + j);
				j--;
				i--;
				break;
			}
		}

		if (ents.size() == 0)
		{
			break;
		}
	}

}
