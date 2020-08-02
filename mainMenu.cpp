#include "mainMenu.h"
#include "SceneManager.h"

MainMenu::MainMenu(std::shared_ptr<SceneManager> Sman, std::shared_ptr<entitymanager> myman) : scene(Sman) // setup for our main menu
{
	myworld = std::make_shared<world>(myman);
	myworld->setmaincam(std::make_shared<maincamera>());
	SDL_ShowCursor(SDL_ENABLE);
}

void MainMenu::init()
{
	MyManager = std::make_shared<ACC::System_Manager>(getself(), myworld);
	myworld->getmaincam()->setposition(glm::vec3(0.1,0.1,-10));
	myworld->getmaincam()->setProjection(glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f));
	myworld->getmaincam()->setView(glm::mat4(glm::lookAt(myworld->getmaincam()->getpos(), glm::vec3(0, 0, 0.1), glm::vec3(0, 1, 0))));
	menustats = std::make_shared<menutrans>();

	myworld->returnmanager()->createMazeText(glm::vec3(glm::vec3(0.0, 1.3, -6)));

	myworld->returnmanager()->createplaybutton(glm::vec3(1.8,.5,-6));

	myworld->returnmanager()->createquitbutton(glm::vec3(1.85, -0.5, -6));

	std::shared_ptr<menuSystem> menusyem = std::make_shared<menuSystem>(myworld, menustats);
	MyManager->addsystem(menusyem);

	std::shared_ptr<modelmatrixsystem> modelup = std::make_shared<modelmatrixsystem>(myworld);
	MyManager->addsystem(modelup);

	std::shared_ptr<RenderSystem> myrendersystem = std::make_shared<RenderSystem>(myworld);
	MyManager->setrender(myrendersystem);

	MyManager->updatesystements();

}

void MainMenu::update(float dt, bool & go)
{
	if (menustats->change == true) //check for gui menu clicks for changing scene
	{
		if (menustats->changetype == menustats->quit)
		{
			go = false;
		}
		else if (menustats->changetype == menustats->play)
		{
			myscenemanager->changescene(std::make_shared<Maingame>(myscenemanager, myworld->returnmanager()));
		}
	}


	MyManager->updatesystements();

	MyManager->update(dt, go); // updata all none render systems

}

void MainMenu::draw(float dt)
{
	bool yes = true;

	MyManager->render(dt, yes); // render our scene 

	MyManager->deletesystements();
	myworld->returnmanager()->cleartodelete();


}

void MainMenu::exit()
{
	myworld->exit();
	myworld.reset();
	MyManager->cleanupsystems();
}
