#pragma once

#include "scene.h"
#include "RenderSystem.h"
#include "Playersystem.h"
#include "modelmatrixsystem.h"
#include "CollisionSystem.h"
#include "AIsystem.h"
#include "MovementSystem.h"
#include "TileMap.h"
#include "crosshairsystem.h"
#include "AnimationSystem.h"
#include "enemyspawner.h"
#include "healthsystem.h"
#include "scorekeeper.h"
#include "ScoreScreen.h"
#include "TextManager.h"

// the assignment main game scene

class Maingame : public scene
{
private:

	std::shared_ptr<world> myworld;
	std::shared_ptr<ACC::System_Manager> MyManager;
	TileMap mymap;
	std::unique_ptr<enemyspawner> enemyspawns;
	std::shared_ptr<ACC::entity> playercheck;
	std::shared_ptr<scorekeeper> myscorekeeper;

public:

	Maingame(std::shared_ptr<SceneManager> Sman, std::shared_ptr<entitymanager> myman);
	void init();
	void update(float dt, bool &go);
	void draw(float dt);
	void exit();



};