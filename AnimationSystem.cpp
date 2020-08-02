#include "AnimationSystem.h"

animationsystem::animationsystem(std::shared_ptr<world> w) : System(w)
{
	my_System_Name = "AnimationSystem";

}

void animationsystem::soiwant(std::vector<std::shared_ptr<ACC::entity>> ent)
{
	for (int i = 0; i < ent.size(); i++)
	{
		if (ent[i]->doihave(animationholdercomp::TypeID))
		{
			connectedents.push_back(ent[i]);
		}
	}

}

void animationsystem::update(float & dt, bool & go) //update connected entities 
{ 
	for (auto ents : connectedents)
	{
		std::shared_ptr<animationholdercomp> myproperties = ents->getcomponent<animationholdercomp>();
		std::shared_ptr<transposecomponent> ownertrans = myproperties->myowner->getcomponent<transposecomponent>();
		std::shared_ptr<directioncomponent> ownerdir = myproperties->myowner->getcomponent<directioncomponent>();

		if (myproperties->mytype == myproperties->light)
		{
			std::shared_ptr<lightcomp> mylight = ents->getcomponent<lightcomp>();
			if (mylight->mylight->returnlighttype() == Slight)
			{
				std::shared_ptr<spotlight> myspot = std::static_pointer_cast<spotlight>(mylight->mylight);
				glm::vec3 newpos = ownertrans->position + (ownertrans->myquat * myproperties->offset);
				myspot->setpos(newpos);
				myspot->setdir(ownerdir->newdirect);
			}
		}
	}

}

void animationsystem::doihave(std::vector<std::shared_ptr<ACC::entity>> ent)
{
	std::vector<std::shared_ptr<ACC::entity>> ents = ent;

	for (int i = 0; i < connectedents.size(); i++)
	{
		for (int j = 0; j < ents.size(); j++)
		{
			if (connectedents[i] == ents[j])
			{
				connectedents.erase(connectedents.begin() + i);
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
