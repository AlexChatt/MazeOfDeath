#include "CollisionSystem.h"

CollisionSystem::CollisionSystem(std::shared_ptr<world> w) : System(w)
{
	my_System_Name = "CollisionSystem";
}

void CollisionSystem::soiwant(std::vector<std::shared_ptr<ACC::entity>> ent)
{
	QuadTree *root = myworld->returnquad();
	std::vector<unsigned long int> lookfor;
	lookfor.push_back(transposecomponent::TypeID);
	lookfor.push_back(collisioncomp::TypeID);

	for (int i = 0; i < ent.size(); i++)
	{
		if (ent[i]->doihave(lookfor))
		{
			std::shared_ptr<collisioncomp> entcoldata = ent[i]->getcomponent<collisioncomp>();
			collisionEnts.push_back(ent[i]);
			Quadinfo newinfo;
			newinfo.objectaabb = entcoldata->myAABB;
			newinfo.objectobb = entcoldata->myobb;
			newinfo.unitID = ent[i]->returnID();
			newinfo.cantmove = entcoldata->imstatic;
			root->addobject(newinfo);
		}

	}


}

void CollisionSystem::update(float & dt, bool & go) //get all collisions and deal with them and resolve 
{
	QuadTree *root = myworld->returnquad();

	for (int i = 0; i < collisionEnts.size(); i++)
	{
		std::shared_ptr<collisioncomp> entcoldata = collisionEnts[i]->getcomponent<collisioncomp>();
		std::shared_ptr<transposecomponent> enttrans = collisionEnts[i]->getcomponent<transposecomponent>();
		std::shared_ptr<velocitycomp> entonevel = collisionEnts[i]->getcomponent<velocitycomp>();
		glm::vec3 posent1 = enttrans->position;

		if (entonevel != NULL)
		{
			posent1 += entonevel->velocity * dt;
		}

		entcoldata->myAABB->update(enttrans->myquat, posent1);
		entcoldata->myobb->update(posent1, enttrans->myquat);
	}

	root->update();

	dealwithcols();

	root = NULL;

}

void CollisionSystem::dealwithcols() //collision resolving 
{
	QuadTree *root = myworld->returnquad();
	bool removefrom = false;

	std::vector<collisioninfo> mycols = root->returncolls();

	for (int i = 0; i < mycols.size(); i++)
	{
		removefrom = false;

		std::shared_ptr<ACC::entity> entone = myworld->returnmanager()->getentfromid(mycols[i].ID1);
		std::shared_ptr<ACC::entity> enttwo = myworld->returnmanager()->getentfromid(mycols[i].ID2);

		std::shared_ptr<collisioncomp> entonecol = entone->getcomponent<collisioncomp>();
		std::shared_ptr<collisioncomp> enttwocol = enttwo->getcomponent<collisioncomp>();


		if (mycols[i].ID1move == true)
		{
			std::shared_ptr<transposecomponent> entonetrans = entone->getcomponent<transposecomponent>();
			std::shared_ptr<velocitycomp> entonevel = entone->getcomponent<velocitycomp>();
			entonetrans->position += (mycols[i].projectionaxis * (mycols[i].overlap)) * 3.0f;
			if (entonevel)
			{
				entonevel->velocity = glm::vec3(0, 0, 0);
			}
		}
		else
		{
			std::shared_ptr<transposecomponent> enttwotrans = enttwo->getcomponent<transposecomponent>();
			std::shared_ptr<velocitycomp> enttwovel = entone->getcomponent<velocitycomp>();
			enttwotrans->position += (mycols[i].projectionaxis * (mycols[i].overlap)) * 3.0f;
			if (enttwovel)
			{
				enttwovel->velocity = glm::vec3(0, 0, 0);
			}
		}
		if (entonecol->effected)
		{
			myworld->returnmanager()->addtodeletelist(entone);
			root->removethis(entone->returnID(), removefrom);
		}
		if (enttwocol->effected)
		{
			myworld->returnmanager()->addtodeletelist(enttwo);
			root->removethis(enttwo->returnID(), removefrom);
		}
			
		if (!entonecol->imstatic && !enttwocol->imstatic)
		{
			healthanddamage(entone, enttwo);
		}	
	}

	root->clearcols();

	root = NULL;
}

void CollisionSystem::healthanddamage(std::shared_ptr<ACC::entity> entone, std::shared_ptr<ACC::entity> enttwo) //damage and other properties resolving
{
	std::shared_ptr<healthcomponent> entonehealth = entone->getcomponent<healthcomponent>();
	std::shared_ptr<healthcomponent> enttwohealth = enttwo->getcomponent<healthcomponent>();

	std::shared_ptr<damagedelt> entonedamage = entone->getcomponent<damagedelt>();
	std::shared_ptr<damagedelt> enttwodamage = enttwo->getcomponent<damagedelt>();

	std::shared_ptr<namecomp> entonename = entone->getcomponent<namecomp>();
	std::shared_ptr<namecomp> enttwoname = enttwo->getcomponent<namecomp>();


	if (entonehealth && enttwodamage)
	{
		if (entonename->myname != enttwoname->myname)
		{
			entonehealth->health -= enttwodamage->damage;
		}
	}
	if (enttwohealth && entonedamage)
	{
		if (entonename->myname != enttwoname->myname)
		{
			enttwohealth->health -= entonedamage->damage;
		}
	}


}

void CollisionSystem::doihave(std::vector<std::shared_ptr<ACC::entity>> ent)
{
	std::vector<std::shared_ptr<ACC::entity>> ents = ent;

	for (int i = 0; i < collisionEnts.size(); i++)
	{
		for (int j = 0; j < ents.size(); j++)
		{
			if (collisionEnts[i] == ents[j])
			{
				collisionEnts.erase(collisionEnts.begin() + i);
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
