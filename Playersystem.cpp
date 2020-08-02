#include "Playersystem.h"

Playersystem::Playersystem(std::shared_ptr<world> w) : System(w)
{
	my_System_Name = "Playersystem";
}

void Playersystem::soiwant(std::vector<std::shared_ptr<ACC::entity>> ent)
{
	std::vector<unsigned long int> lookfor;
	lookfor.push_back(transposecomponent::TypeID);
	lookfor.push_back(playercomp::TypeID);
	lookfor.push_back(speedcomp::TypeID);
	lookfor.push_back(directioncomponent::TypeID);
	lookfor.push_back(attackspeedcomp::TypeID);
	lookfor.push_back(velocitycomp::TypeID);

	for (int i = 0; i < ent.size(); i++)
	{
		if (ent[i]->doihave(lookfor))
		{
			players.push_back(ent[i]);
			std::shared_ptr<transposecomponent> playertrans = ent[i]->getcomponent<transposecomponent>();
			myworld->getmaincam()->getplayerpos(playertrans);

		}
	}

}

void Playersystem::update(float & dt, bool & go) //deal with the players movment and actions (like fireing bullets)
{
	for (auto player : players)
	{
		std::shared_ptr<transposecomponent> playertrans = player->getcomponent<transposecomponent>();
		std::shared_ptr<directioncomponent> playerdir = player->getcomponent<directioncomponent>();
		std::shared_ptr<speedcomp> playerspeed = player->getcomponent<speedcomp>();
		std::shared_ptr<attackspeedcomp> playyerattackspeed = player->getcomponent<attackspeedcomp>();
		std::shared_ptr<velocitycomp> playervel = player->getcomponent<velocitycomp>();

		playervel->velocity = glm::vec3(0, 0, 0);

		playyerattackspeed->currectattacktime += dt;

		if (inputlogger::instance().getkeydown(SDLK_w))
		{
			playervel->velocity += (-glm::vec3(1,0,0) * playerspeed->speed);
		}
		if (inputlogger::instance().getkeydown(SDLK_s))
		{
			playervel->velocity += (glm::vec3(1, 0, 0) * playerspeed->speed);
		}
		if (inputlogger::instance().getkeydown(SDLK_a))
		{
			playervel->velocity += (glm::vec3(0, 0, 1) * playerspeed->speed);
		}
		if (inputlogger::instance().getkeydown(SDLK_d))
		{
			playervel->velocity += (-glm::vec3(0, 0, 1) * playerspeed->speed);
		}

		playerdir->newdirect = playertrans->myquat * playerdir->direction;

		if (inputlogger::instance().getleftmouse())
		{
			if (playyerattackspeed->currectattacktime >= playyerattackspeed->attackspeed)
			{
				myworld->returnmanager()->createbullet(playertrans->position + glm::vec3(0,1,0) + (playerdir->newdirect * 0.4f) , playertrans->myquat, player->returnID()); //fire a bullet
				playyerattackspeed->currectattacktime = 0.0;
			}
		}

		playertrans->position.y = 0;
	}




}

void Playersystem::doihave(std::vector<std::shared_ptr<ACC::entity>> ent)
{
	std::vector<std::shared_ptr<ACC::entity>> ents = ent;

	for (int i = 0; i < players.size(); i++)
	{
		for (int j = 0; j < ents.size(); j++)
		{
			if (players[i] == ents[j])
			{
				players.erase(players.begin() + i);
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
