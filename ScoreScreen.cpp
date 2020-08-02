#include "ScoreScreen.h"
#include "SceneManager.h"

ScoreScreen::ScoreScreen(std::shared_ptr<SceneManager> Sman, std::shared_ptr<entitymanager> myman, std::shared_ptr<scorekeeper> FS) : scene(Sman) //our score screen menu
{
	myworld = std::make_shared<world>(myman);
	finalscore = FS;
	myworld->setmaincam(std::make_shared<maincamera>());
	SDL_ShowCursor(SDL_ENABLE);
}

void ScoreScreen::init() //system and entity setup
{
	MyManager = std::make_shared<ACC::System_Manager>(getself(), myworld);
	myworld->getmaincam()->setposition(glm::vec3(0.1, 0.1, -10));
	myworld->getmaincam()->setProjection(glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f));
	myworld->getmaincam()->setView(glm::mat4(glm::lookAt(myworld->getmaincam()->getpos(), glm::vec3(0, 0, 0.1), glm::vec3(0, 1, 0))));
	menustats = std::make_shared<menutrans>();

	myworld->returnmanager()->createdeathtext(glm::vec3(glm::vec3(0.0, 1.3, -6)));

	myworld->returnmanager()->createbackbutton(glm::vec3(1.6, .5, -6));

	myworld->returnmanager()->createquitbutton(glm::vec3(1.85, -0.5, -6));

	std::shared_ptr<menuSystem> menusyem = std::make_shared<menuSystem>(myworld, menustats);
	MyManager->addsystem(menusyem);

	std::shared_ptr<modelmatrixsystem> modelup = std::make_shared<modelmatrixsystem>(myworld);
	MyManager->addsystem(modelup);

	std::shared_ptr<RenderSystem> myrendersystem = std::make_shared<RenderSystem>(myworld);
	MyManager->setrender(myrendersystem);

	MyManager->updatesystements();

}


void ScoreScreen::update(float dt, bool & go)
{
	if (menustats->change == true) //check for wanted menu changes 
	{
		if (menustats->changetype == menustats->quit)
		{
			go = false;
		}
		else if (menustats->changetype == menustats->play)
		{
			myscenemanager->changescene(std::make_shared<Maingame>(myscenemanager, myworld->returnmanager()));
		}
		else if (menustats->changetype == menustats->backtomain)
		{
			myscenemanager->changescene(std::make_shared<MainMenu>(myscenemanager, myworld->returnmanager()));
		}
	}


	MyManager->updatesystements();

	MyManager->update(dt, go); // updata all none render systems

}

void ScoreScreen::draw(float dt)
{
	bool yes = true;

	MyManager->render(dt, yes); // render our scene 

	std::string scoretotext = "Final Score " + std::to_string((int)finalscore->score);

	TextManager::instance().rendertext(scoretotext, glm::vec3(1.0f, 0.0, 0.0), 500, 360.0f, 1.0f);

	MyManager->deletesystements();
	myworld->returnmanager()->cleartodelete();


}

void ScoreScreen::exit()
{
	myworld->exit();
	myworld.reset();
	MyManager->cleanupsystems();
}
