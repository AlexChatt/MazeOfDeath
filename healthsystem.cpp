#include "healthsystem.h"

healthsystem::healthsystem(std::shared_ptr<world> w, std::shared_ptr<scorekeeper> sk) : System(w)
{
	my_System_Name = "healthsystem";
	myscorekeeper = sk;

}

void healthsystem::soiwant(std::vector<std::shared_ptr<ACC::entity>> ent)
{
	for (int i = 0; i < ent.size(); i++)
	{
		if (ent[i]->doihave(healthcomponent::TypeID))
		{
			healthents.push_back(ent[i]);
		}
	}

}

void healthsystem::update(float & dt, bool & go) //update and check all the healths of our entities and make sure they are above 0
{
	QuadTree *root = myworld->returnquad();

	bool removefrom = false;

	for (auto ent : healthents)
	{
		std::shared_ptr<healthcomponent> myhealth = ent->getcomponent<healthcomponent>();
		if (myhealth->health <= 0)
		{
			myworld->returnmanager()->addtodeletelist(ent);
			std::shared_ptr<collisioncomp> mycol = ent->getcomponent<collisioncomp>();
			if (mycol)
			{
				removefrom = false;
				root->removethis(ent->returnID(), removefrom);
			}

			std::shared_ptr<namecomp> myname = ent->getcomponent<namecomp>();

			if (myname->myname == "enemy")
			{
				myscorekeeper->score += 100;
			}

		}
	}

}

void healthsystem::doihave(std::vector<std::shared_ptr<ACC::entity>> ent)
{
	std::vector<std::shared_ptr<ACC::entity>> ents = ent;

	for (int i = 0; i < healthents.size(); i++)
	{
		for (int j = 0; j < ents.size(); j++)
		{
			if (healthents[i] == ents[j])
			{
				healthents.erase(healthents.begin() + i);
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
