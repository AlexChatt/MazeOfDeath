#pragma once

#include "scene.h"
#include "RenderSystem.h"
#include "modelmatrixsystem.h"
#include "menutrans.h"
#include "MenuSystem.h"
#include <memory>
#include "MainGame.h"
#include "mainMenu.h"
#include "scorekeeper.h"

// our end game score screen

class ScoreScreen : public scene
{
private:

	std::shared_ptr<world> myworld;
	std::shared_ptr<ACC::System_Manager> MyManager;
	std::shared_ptr<menutrans> menustats;
	std::shared_ptr<scorekeeper> finalscore;

public:

	ScoreScreen(std::shared_ptr<SceneManager> Sman, std::shared_ptr<entitymanager> myman, std::shared_ptr<scorekeeper> FS);
	void init();
	void update(float dt, bool &go);
	void draw(float dt);
	void exit();



};