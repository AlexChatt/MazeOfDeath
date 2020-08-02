#include "QuadTree.h"

void QuadTree::construct(QuadTree *parent, int divides) //create our quadtree with the number of divides we want
{
	root = parent;

	if (parent == NULL)
	{
		mycols = std::make_shared<collison>();
	}

	if (divides != 0)
	{
		divides--;
		child1 = new QuadTree(quadmin, middle);
		child1->setcoldatabase(mycols);
		child1->construct(this, divides);
		child2 = new QuadTree(middle, quadmax);
		child2->setcoldatabase(mycols);
		child2->construct(this, divides);
		child3 = new QuadTree(glm::vec3(middle.x, quadmin.y, quadmin.z), glm::vec3(quadmax.x, quadmin.y, middle.z));
		child3->setcoldatabase(mycols);
		child3->construct(this, divides);
		child4 = new QuadTree(glm::vec3(quadmin.x, quadmin.y, middle.z), glm::vec3(middle.x, quadmin.y, quadmax.z));
		child4->setcoldatabase(mycols);
		child4->construct(this, divides);
	}

}

void QuadTree::removeentity(int ID) //remove unneeded ent
{
	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i].unitID == ID)
		{
			objects.erase(objects.begin() + i);
			break;
		}
	}

}


void QuadTree::getparententities(std::vector<Quadinfo> &returnents) //get all of our parents col datas 
{
	if (root != NULL)
	{
		root->getparententities(returnents);
	}

	if (objects.size() == 0)
	{
		return;
	}
	else
	{
		returnents.insert(returnents.begin(), objects.begin(), objects.end());
	}
}

void QuadTree::collisiondetection() //now check for all collisions on this current frame and store them into the colliison class
{
	if (objects.size() != 0)
	{
		std::vector<Quadinfo> entstocheck = objects;
		std::vector<Quadinfo> parentent;
		if (root != NULL)
		{
			root->getparententities(parentent);
		}

		entstocheck.insert(entstocheck.end(), parentent.begin(), parentent.end());

		for (int i = 0; i < objects.size(); i++)
		{
			std::shared_ptr<AABB> myaabb = objects[i].objectaabb;
			
			for (int j = i + 1; j < entstocheck.size(); j++)
			{
				int id1 = objects[i].unitID;
				int id2 = entstocheck[j].unitID;

				if ((id1 != id2) && !(objects[i].cantmove == true && entstocheck[j].cantmove == true))
				{
					std::shared_ptr<AABB> otheraabb = entstocheck[j].objectaabb;
		
					if (myaabb->collision(otheraabb))
					{	
						std::shared_ptr<OBB> myobb = objects[i].objectobb;
						std::shared_ptr<OBB> otherobb = entstocheck[j].objectobb;
						glm::vec3 axisofcol;
						float overlapofcol = 100000000.0f;

						if (myobb->collisontest2(otherobb, axisofcol, overlapofcol))
						{
							collisioninfo newcol;
							newcol.ID1 = objects[i].unitID;
							newcol.ID2 = entstocheck[j].unitID;
							newcol.projectionaxis = axisofcol;

							if (entstocheck[i].cantmove == true)
							{
								glm::vec3 oneside = otherobb->returncenter() + (axisofcol * overlapofcol);
								glm::vec3 otherside = otherobb->returncenter() + (axisofcol * -overlapofcol);
								newcol.ID1move = false;
								if (glm::length(oneside - myobb->returncenter()) < glm::length(otherside - myobb->returncenter()))
								{
									newcol.overlap = -overlapofcol;
								}
								else
								{
									newcol.overlap = overlapofcol;
								}

							}
							else if (entstocheck[j].cantmove == true || entstocheck[i].cantmove == false)
							{
								newcol.ID1move = true;
								glm::vec3 oneside = myobb->returncenter() + (axisofcol * overlapofcol);
								glm::vec3 otherside = myobb->returncenter() + (axisofcol * -overlapofcol);
								if (glm::length(oneside - otherobb->returncenter()) < glm::length(otherside - otherobb->returncenter()))
								{
									newcol.overlap = -overlapofcol;
								}
								else
								{
									newcol.overlap = overlapofcol;
								}
							}

							mycols->addcol(newcol);
						}
					}
				}

			}
		}
	}
	
}

bool QuadTree::fitinoct(glm::vec3 objmin, glm::vec3 objmax,QuadTree* lanode) //check if an entity still fits in this node
{
	if (objmin.x > lanode->quadmin.x && objmin.x < lanode->quadmax.x && objmax.x > lanode->quadmin.x && objmax.x < lanode->quadmax.x)
	{
		if (objmin.z > lanode->quadmin.z && objmin.z < lanode->quadmax.z && objmax.z > lanode->quadmin.z && objmax.z < lanode->quadmax.z)
		{
			return true;
		}
	}

	return false;
}

void QuadTree::update() //update all our collison data then check for collisons
{

	checkendts();
	if (child1 != NULL)
	{
		child1->checkendts();
		child2->checkendts();
		child3->checkendts();
		child4->checkendts();
	}

	collisiondetection();

	if (child1 != NULL)
	{
		child1->update();
		child2->update();
		child3->update();
		child4->update();
	}

}

void QuadTree::addobject(Quadinfo obj) //add an object
{
	if (root != NULL && !fitinoct(obj.objectaabb->newmin, obj.objectaabb->newmax, this))
	{
		root->addobject(obj);
	}
	else if (child1 == NULL)
	{
		objects.push_back(obj);
		return;
	}
	else if (fitinoct(obj.objectaabb->newmin, obj.objectaabb->newmax, child1))
	{
		child1->addobject(obj);
		return;
	}
	else if (fitinoct(obj.objectaabb->newmin, obj.objectaabb->newmax, child2))
	{
		child2->addobject(obj);
		return;
	}
	else if (fitinoct(obj.objectaabb->newmin, obj.objectaabb->newmax, child3))
	{
		child3->addobject(obj);
		return;
	}
	else if (fitinoct(obj.objectaabb->newmin, obj.objectaabb->newmax, child4))
	{
		child4->addobject(obj);
		return;
	}
	else
	{
		objects.push_back(obj);
		return;
	}


}

void QuadTree::checkendts() // move entities around if neeeded
{
	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i].cantmove != true)
		{
			Quadinfo obj = objects[i];

			if (root != NULL && !fitinoct(obj.objectaabb->newmin, obj.objectaabb->newmax, this))
			{
				objects.erase(objects.begin() + i);
				i--;
				root->addobject(obj);
			}
			else if (child1 == NULL)
			{

			}
			else if (fitinoct(obj.objectaabb->newmin, obj.objectaabb->newmax, child1))
			{
				objects.erase(objects.begin() + i);
				i--;
				child1->addobject(obj);
			}
			else if (fitinoct(obj.objectaabb->newmin, obj.objectaabb->newmax, child2))
			{
				objects.erase(objects.begin() + i);
				i--;
				child2->addobject(obj);
			}
			else if (fitinoct(obj.objectaabb->newmin, obj.objectaabb->newmax, child3))
			{
				objects.erase(objects.begin() + i);
				i--;
				child3->addobject(obj);
			}
			else if (fitinoct(obj.objectaabb->newmin, obj.objectaabb->newmax, child4))
			{
				objects.erase(objects.begin() + i);
				i--;
				child4->addobject(obj);
			}
		
		}
	}


}

void QuadTree::cleanup() //clean up our quad
{
	if (child1 != NULL)
	{
		child1->cleanup();
		child2->cleanup();
		child3->cleanup();
		child4->cleanup();

		delete child1;
		delete child2;
		delete child3;
		delete child4;
	}

}

void QuadTree::removethis(unsigned long int id, bool &found) //remove an entity from our quad tree
{
	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i].unitID == id)
		{
			objects.erase(objects.begin() + i);
			found = true;
			return;
		}
	}

	if (child1 != NULL)
	{
		child1->removethis(id,found);
		if (found)
		{
			return;
		}
		child2->removethis(id, found);
		if (found)
		{
			return;
		}
		child3->removethis(id, found);
		if (found)
		{
			return;
		}
		child4->removethis(id, found);
		if (found)
		{
			return;
		}
	}

}



