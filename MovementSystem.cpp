#include "MovementSystem.h"

MovementSystem::MovementSystem(std::shared_ptr<world> w) : System(w)
{
	my_System_Name = "MovementSystem";

}

void MovementSystem::soiwant(std::vector<std::shared_ptr<ACC::entity>> ent)
{
	std::vector<unsigned long int> lookfor;
	lookfor.push_back(transposecomponent::TypeID);
	lookfor.push_back(velocitycomp::TypeID);

	for (int i = 0; i < ent.size(); i++)
	{
		if (ent[i]->doihave(lookfor))
		{
			moveingents.push_back(ent[i]);
		}
	}
}

void MovementSystem::update(float & dt, bool & go) //deal with the movemnet of all our entities 
{
	for (auto ent : moveingents)
	{
		std::shared_ptr<velocitycomp> entvel = ent->getcomponent<velocitycomp>();
		std::shared_ptr<transposecomponent> enttra = ent->getcomponent<transposecomponent>();
		enttra->position += entvel->velocity * dt;
	}

	myworld->getmaincam()->setView();
}

void MovementSystem::doihave(std::vector<std::shared_ptr<ACC::entity>> ent)
{

	std::vector<std::shared_ptr<ACC::entity>> ents = ent;

	for (int i = 0; i < moveingents.size(); i++)
	{
		for (int j = 0; j < ents.size(); j++)
		{
			if (moveingents[i] == ents[j])
			{
				moveingents.erase(moveingents.begin() + i);
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
