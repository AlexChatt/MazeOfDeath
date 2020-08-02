#pragma once

#include "entity.h"
#include "ID_manager.h"
#include "component.h"
#include "dirlight.h"
#include "spotlight.h"
#include <gtc/matrix_transform.hpp> 
#include <memory>
#include "Resourcemanager.h"
#include <unordered_map>


// the entity manager for creating and holding entities
class entitymanager
{
private:
	ID_manager IDs;

	std::unordered_map<unsigned long int,std::shared_ptr<ACC::entity>> entities;
	std::vector<std::shared_ptr<ACC::entity>> tooadd;
	std::vector<std::shared_ptr<ACC::entity>> todelete;

public:

	void create_skybox();
	void create_directionlight(std::shared_ptr<dirlight> mydirinfo);
	void createflashlight(std::shared_ptr<ACC::entity> parent);
	std::shared_ptr<ACC::entity> createPlayer(glm::vec3 pos, std::shared_ptr<transposecomponent> playtrans);
	void createEnemy(glm::vec3 pos);
	void createFloor(glm::vec3 pos);
	void createWall(glm::vec3 pos);
	void createbullet(glm::vec3 pos, glm::quat orin,unsigned long int ownerID);
	void createcrosshair(glm::vec3 pos);
	void createplaybutton(glm::vec3 pos);
	void createbackbutton(glm::vec3 pos);
	void createquitbutton(glm::vec3 pos);
	void createMazeText(glm::vec3 pos);
	void createdeathtext(glm::vec3 pos);

	entitymanager();

	void delete_entity();

	std::vector<std::shared_ptr<ACC::entity>> returntoadd()
	{
		return tooadd;
	}

	std::vector<std::shared_ptr<ACC::entity>> returntodelete()
	{
		return todelete;
	}

	void cleartoadd()
	{
		tooadd.clear();
	}

	void cleartodelete();

   std::unordered_map<unsigned long int,std::shared_ptr<ACC::entity>> returnentities() // return all our entites
   {
	  return entities;
   }

   std::shared_ptr<ACC::entity> getentfromid(unsigned long int ID)
   {
	   return entities[ID];
   }

   void addtodeletelist(std::shared_ptr<ACC::entity> deleteme)
   {
	   todelete.push_back(deleteme);
   }

};
