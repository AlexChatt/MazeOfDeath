#pragma once

#include "OBB.h"
#include <glm.hpp>
#include <memory>
#include "QuadInfo.h"
#include <iostream>
#include "collisioninfo.h"

//our quadtree that will help make collision detection alot cheaper and efficent (ray pointer needed for recursive problems)

class QuadTree 
{
private:

	glm::vec3 quadmin;
	glm::vec3 quadmax;
	glm::vec3 middle;

	QuadTree *root;
	QuadTree *child1;
	QuadTree *child2;
	QuadTree *child3;
	QuadTree *child4;
	std::vector<Quadinfo> objects;
	std::shared_ptr<collison> mycols;


public:

	QuadTree(glm::vec3 minim, glm::vec3 maxim)
	{
		quadmin = minim;
		quadmax = maxim;
		glm::vec3 temp = quadmax - quadmin;
		middle = quadmin + (temp / 2.0f);
	}

	void setcoldatabase(std::shared_ptr<collison> c)
	{
		mycols = c;
	}

	void construct(QuadTree *parent, int divides);
	void removeentity(int ID);
	void getparententities(std::vector<Quadinfo> &returnents);
	void collisiondetection();
	bool fitinoct(glm::vec3 objmin, glm::vec3 objmax, QuadTree *lanode);
	void update();
	void addobject(Quadinfo obj);
	void checkendts();

	std::vector<collisioninfo> returncolls()
	{
		return mycols->returncol();
	}

	void clearcols()
	{
		mycols->clearall();
	}

	void cleanup();

	void removethis(unsigned long int id, bool &found);


};