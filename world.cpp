#include "world.h"
 
world::world(std::shared_ptr<entitymanager> getent) //add manager to world 
{
	myentmanager = getent;
}

void world::init()
{

}

void world::exit() //entity manager cleanup
{
	myentmanager->delete_entity();

}

void world::setquad(QuadTree *myQ) //add quad tree 
{
	myquadtree = myQ;

}

void world::setpath(std::shared_ptr<pathfinding> PathFin) //set pathfinder
{
	mypathfinder = PathFin;
}

std::shared_ptr<entitymanager> world::returnmanager()
{
	return myentmanager;
}


