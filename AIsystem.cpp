#include "AIsystem.h"

AIsystem::AIsystem(std::shared_ptr<world> w) : System(w)
{
	my_System_Name = "AIsystem";
}

void AIsystem::soiwant(std::vector<std::shared_ptr<ACC::entity>> ent) 
{
	for (int i = 0; i < ent.size(); i++)
	{
		if (ent[i]->doihave(playercomp::TypeID) && player == NULL)
		{
			player = ent[i];
		}
		else if (ent[i]->doihave(AIcomp::TypeID))
		{
			AIs.push_back(ent[i]);
		}

	}
}

void AIsystem::update(float & dt, bool & go) //update all of our ai entities 
{
	for (auto AIent : AIs)
	{
		std::shared_ptr<AIcomp> aicom = AIent->getcomponent<AIcomp>();
		if (aicom->mystate == aicom->idel)
		{
			std::shared_ptr<transposecomponent> aitrans = AIent->getcomponent<transposecomponent>();
			std::shared_ptr<transposecomponent> playertrans = player->getcomponent<transposecomponent>();

			aicom->postogo = myworld->getpathfinder()->getpathto(playertrans->position,aitrans->position);
			myworld->getpathfinder()->clear();

			aicom->mystate = aicom->attack;
		}
		else if(aicom->mystate == aicom->attack)
		{
			std::shared_ptr<transposecomponent> aitrans = AIent->getcomponent<transposecomponent>();
			std::shared_ptr<velocitycomp> aivel = AIent->getcomponent<velocitycomp>();
			std::shared_ptr<speedcomp> aispeed = AIent->getcomponent<speedcomp>();
			std::shared_ptr<transposecomponent> playertrans = player->getcomponent<transposecomponent>();

			if (aicom->recaltime >= 0.3)
			{
				aicom->postogo = myworld->getpathfinder()->getpathto(playertrans->position, aitrans->position);

				if (aicom->postogo.size() > 2)
				{
					if (glm::length(aitrans->position - aicom->postogo[0]) > glm::length(aitrans->position - aicom->postogo[1]))
					{
						aicom->postogo.erase(aicom->postogo.begin() + 0);
					}
					
				}

				myworld->getpathfinder()->clear();
				aicom->recaltime = 0.0f;
			}
			else
			{
				aicom->recaltime += dt;
			}

			if (aicom->postogo.size() > 0)
			{
				if (glm::length(aicom->postogo[0] - aitrans->position) <= 0.3)
				{
					aicom->postogo.erase(aicom->postogo.begin() + 0);
				}
				else
				{
					glm::vec3 gotoppos = aicom->postogo[0] - aitrans->position;
					aivel->velocity = glm::normalize(gotoppos) * aispeed->speed;
					glm::vec3 toolookat = glm::normalize(aitrans->position - playertrans->position);
					glm::vec3 tolookat = aitrans->position + glm::vec3(toolookat.x, playertrans->position.y, toolookat.z);
					aitrans->myquat = glm::toQuat(glm::transpose(glm::lookAt(aitrans->position, tolookat, glm::vec3(0, 1, 0))));
				}
			}
			else
			{
				aivel->velocity = glm::vec3(0, 0, 0);
			}
			aitrans->position.y = 0;

		}
	}


}

void AIsystem::doihave(std::vector<std::shared_ptr<ACC::entity>> ent)
{
	std::vector<std::shared_ptr<ACC::entity>> ents = ent;

	for (int i = 0; i < ents.size(); i++)
	{
		if (ents[i] == player)
		{
			player = NULL;
			ents.erase(ents.begin() + i);
			i--;
		}
		else
		{
			for (int j = 0; j < AIs.size(); j++)
			{
				if (AIs[j] == ents[i])
				{
					ents.erase(ents.begin() + i);
					i--;
					AIs.erase(AIs.begin() + j);
					j--;
					break;
				}
			}
		}

	}

}
