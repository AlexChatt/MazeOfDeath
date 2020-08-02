#pragma once

#include "component.h"
#include "entitymanager.h"
#include "Tile.h"

//class that controles when to spawn enemies

class enemyspawner
{
private:

	std::shared_ptr<entitymanager> mymanager;
	std::shared_ptr<transposecomponent> playertrans;
	std::vector<std::vector<Tile>> tilemap;

	float spawntimer;
	float currenttime;

public:

	enemyspawner()
	{
		currenttime = 2;
		spawntimer = 1;
	}

	void setentmanager(std::shared_ptr<entitymanager> e)
	{
		mymanager = e;
	}

	void setplayer(std::shared_ptr<transposecomponent> ptrans)
	{
		 playertrans = ptrans;
	}

	void setthemap(std::vector<std::vector<Tile>> map)
	{
		tilemap = map;
	}


	void update(float dt);

};