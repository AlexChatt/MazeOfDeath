#pragma once

#include "scene.h"
#include "RenderSystem.h"
#include "modelmatrixsystem.h"
#include "menutrans.h"
#include "MenuSystem.h"
#include <memory>
#include "MainGame.h"
#include "TextManager.h"

// main menu for game

class MainMenu : public scene
{
private:

	std::shared_ptr<world> myworld;
	std::shared_ptr<ACC::System_Manager> MyManager;
	std::shared_ptr<menutrans> menustats;

public:

	MainMenu(std::shared_ptr<SceneManager> Sman, std::shared_ptr<entitymanager> myman);
	void init();
	void update(float dt, bool &go);
	void draw(float dt);
	void exit();



};