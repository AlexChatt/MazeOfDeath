#include "MainGame.h"
#include "SceneManager.h"

Maingame::Maingame(std::shared_ptr<SceneManager> Sman, std::shared_ptr<entitymanager> myman) : scene(Sman) //setup for the maingame (pathfinder, quadtree) 
{
	myworld = std::make_shared<world>(myman);
	myworld->setquad(new QuadTree(glm::vec3(-12, -100, -12), glm::vec3(12, 100, 12)));
	myworld->setpath(std::make_shared<pathfinding>());
	enemyspawns = std::make_unique<enemyspawner>();
	enemyspawns->setentmanager(myman);
	myscorekeeper = std::make_shared<scorekeeper>();
	SDL_ShowCursor(SDL_DISABLE);
}

void Maingame::init() //starting setup
{
	MyManager = std::make_shared<ACC::System_Manager>(getself(), myworld);
	mymap.setup(20, 20, rand() % 300);
	mymap.setobsize(50);
	mymap.createmap();
	myworld->setmaincam(std::make_shared<maincamera>());
	std::vector<std::vector<Tile>> map = mymap.returntilemap();

	myworld->returnmanager()->create_skybox();

	std::shared_ptr<transposecomponent> playertrans = std::make_shared<transposecomponent>();
	playercheck = myworld->returnmanager()->createPlayer(glm::vec3(0 + 0.5, 0, 0 + 0.5), playertrans);
	enemyspawns->setplayer(playertrans);

	for (int i = 0; i < mymap.retwidth(); i++)
	{
		for (int j = 0; j < mymap.retheight(); j++)
		{
			if (map[i][j].obstucted == true)
			{
				myworld->returnmanager()->createWall(map[i][j].position);
			}
			else
			{
				myworld->returnmanager()->createFloor(map[i][j].position);
			}

		}
	}
	enemyspawns->setthemap(map);

	std::shared_ptr<dirlight> themainlight = std::make_shared<dirlight>();
	themainlight->setdir(glm::vec3(0.0, -1.0, 0.0));
	themainlight->setamb(glm::vec3(0.5, 0.5, 0.5));
	themainlight->setlightcolour(glm::vec3(0.1, 0.1, 0.1));
	
	myworld->returnmanager()->create_directionlight(themainlight);

	myworld->returnmanager()->createcrosshair(glm::vec3(5,0,5));

	myworld->returnquad()->construct(NULL, 2);
	myworld->getpathfinder()->createpathmap(mymap.returntilemap(), mymap.retwidth(), mymap.retheight());

	std::shared_ptr<RenderSystem> myrendersystem = std::make_shared<RenderSystem>(myworld);
	MyManager->setrender(myrendersystem);

	std::shared_ptr<Playersystem> playerupdate = std::make_shared<Playersystem>(myworld);
	MyManager->addsystem(playerupdate);

	std::shared_ptr<AIsystem> AIsys = std::make_shared<AIsystem>(myworld);
	MyManager->addsystem(AIsys);

	std::shared_ptr<CollisionSystem> collsys = std::make_shared<CollisionSystem>(myworld);
	MyManager->addsystem(collsys);

	std::shared_ptr<crosshairsystem> crossupdate = std::make_shared<crosshairsystem>(myworld);
	MyManager->addsystem(crossupdate);

	std::shared_ptr<MovementSystem> movesys = std::make_shared<MovementSystem>(myworld);
	MyManager->addsystem(movesys);

	std::shared_ptr<animationsystem> animsystem = std::make_shared<animationsystem>(myworld);
	MyManager->addsystem(animsystem);

	std::shared_ptr<modelmatrixsystem> modelup = std::make_shared<modelmatrixsystem>(myworld);
	MyManager->addsystem(modelup);

	std::shared_ptr<healthsystem> myhealthsystem = std::make_shared<healthsystem>(myworld, myscorekeeper);
	MyManager->addsystem(myhealthsystem);

	MyManager->updatesystements();

	myworld->getmaincam()->setProjection(glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f));

}

void Maingame::update(float dt, bool &go)
{
	if (playercheck == NULL || playercheck->returndeleteme())
	{
		myscenemanager->changescene(std::make_shared<ScoreScreen>(myscenemanager, myworld->returnmanager(),myscorekeeper)); //if the player is dead then we have lost so time to check scenes 
		return;
	}

	enemyspawns->update(dt); 
	MyManager->updatesystements(); //add the new entities created 
	MyManager->update(dt, go); // updata all none render systems

}

void Maingame::draw(float dt)
{
	bool yes = true;

	MyManager->render(dt, yes); // render our scene 

	if (playercheck != NULL || !playercheck->returndeleteme()) 
	{
		std::shared_ptr<healthcomponent> playerhealth = playercheck->getcomponent<healthcomponent>();

		std::string healthtotext = "Health " + std::to_string((int)playerhealth->health);

		TextManager::instance().rendertext(healthtotext, glm::vec3(1.0f, 0.0, 0.0), 1, 10.0f, 0.7f);
	}

	std::string scoretotext = "Score " + std::to_string((int)myscorekeeper->score);

	TextManager::instance().rendertext(scoretotext, glm::vec3(1.0f, 0.0, 0.0), 1000, 10.0f, 0.7f);

	MyManager->deletesystements();
	myworld->returnmanager()->cleartodelete(); //clean up for all dead entities 
}

void Maingame::exit() //clean up for the scene
{

	myworld->returnquad()->cleanup();
	delete myworld->returnquad();
	myworld->exit();
	enemyspawns.release();
	myworld.reset();
	MyManager->cleanupsystems();
}
