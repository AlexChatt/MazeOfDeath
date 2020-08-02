#pragma once
#include "entitymanager.h"
#include <memory>
#include "QuadTree.h"
#include "Pathfinder.h"
#include "maincamera.h"

//our world class that contains its own entity manager aswell as other important classes (each scene has its own world)

class world
{
private:

	std::shared_ptr<entitymanager> myentmanager;
	QuadTree *myquadtree;
	std::shared_ptr<pathfinding> mypathfinder;
	std::shared_ptr<maincamera> maincam;

public:

	world()
	{
		
	}
	world(std::shared_ptr<entitymanager> getent);
	void init();
	void exit();
	void setquad(QuadTree *myQ);
	void setpath(std::shared_ptr<pathfinding> PathFin);
	
	std::shared_ptr<entitymanager> returnmanager();
	QuadTree *returnquad()
	{
		return myquadtree;
	}

	void setmaincam(std::shared_ptr<maincamera> cam)
	{
		maincam = cam;
	}
	std::shared_ptr<maincamera> getmaincam()
	{
		return maincam;
	}
	
	std::shared_ptr<pathfinding> getpathfinder()
	{
		return mypathfinder;
	}
};