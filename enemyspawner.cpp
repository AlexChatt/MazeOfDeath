#include "enemyspawner.h"

void enemyspawner::update(float dt) //check to see if we need to spawn an enemy 
{
	if (currenttime >= spawntimer)
	{
		int randx;
		int randy;

		int width = tilemap.size();
		int height = tilemap[0].size();

		bool foundspawnplace = false;


		while (!foundspawnplace) //make sure we dont spawn the enemy right next to the player
		{
			randx = rand() % 20;
			randy = rand() % 20;

			float lenghttest = glm::length(tilemap[randx][randy].position - playertrans->position);

			if (tilemap[randx][randy].obstucted == false && lenghttest >= 5)
			{
				foundspawnplace = true;
			}
		}


		if (foundspawnplace == true)
		{
			mymanager->createEnemy(tilemap[randx][randy].position);
			currenttime = 0;
		}



	}
	else
	{
		currenttime += dt;
	}



}
