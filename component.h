#pragma once

#include <glm.hpp>
#include "glew.h"
#include <vector>
#include "shader.h"
#include <gtc/quaternion.hpp>
#include <gtx/quaternion.hpp>
#include "Light.h"
#include "dirlight.h"
#include <memory>
#include "model.h"
#include "OBB.h"
#include "AABB.h"

//here is a list of all of our components that we need for the game and the demo. every component is based of the base class ACC:component 
//For use components only contain data while systems do the needed logic

namespace ACC 
{

	class entity;
 
	class component 
	{

	public:

		virtual int GetType() const = 0;
		
	};

}

// typeID is used for getting the component from the entity vector list

class transposecomponent : public ACC::component
{

public:

	static const int TypeID = 1;

	int GetType() const { return TypeID; };

  glm::mat4 modelMatrix;

  glm::vec3 position;

  glm::quat myquat;

  glm::vec3 up;

  glm::vec3 right;

  glm::vec3 forward;

  glm::vec3 scale;

};



class directioncomponent : public ACC::component
{
 public:

	 static const int TypeID = 2;

	 int GetType() const  { return TypeID; };

   glm::vec3 direction;

   glm::vec3 newdirect;

};

class modelcomponent : public ACC::component
{
public:

	static const int TypeID = 3;

	int GetType() const { return TypeID; };

	std::shared_ptr<model> mymodel;
	std::shared_ptr<shader> myshader;

	bool drawme;
	bool effectedbylights;
	float mystrenght;
	float myshine;
	bool depth;

};


class lightcomp : public ACC::component
{
public:


	static const int TypeID = 4;

	int GetType() const { return TypeID; };

	std::shared_ptr<light> mylight;

};


class healthcomponent : public ACC::component
{

public:

	static const int TypeID = 5;

	float health;

	float maxhp;

	bool hitdelete;

	int GetType() const { return TypeID; };

};

class animationholdercomp : public ACC::component
{

public:
	static const int TypeID = 6;

	enum type { light, trans };

	type mytype;

	std::shared_ptr<ACC::entity> myowner;

	glm::vec3 offset;

	int GetType() const { return TypeID; };

};

class playercomp : public ACC::component
{

public:
	static const int TypeID = 7;

	int GetType() const { return TypeID; };

};

class AIcomp : public ACC::component
{
	
public:

	enum state { idel, attack};

	std::vector<glm::vec3> postogo;

	state mystate;

	float recaltime;

	static const int TypeID = 8;

	int GetType() const { return TypeID; };

};

class speedcomp : public ACC::component
{

public:

	static const int TypeID = 9;

	float speed;

	int GetType() const { return TypeID; };

};

class collisioncomp : public ACC::component
{

public:

	static const int TypeID = 10;

	std::shared_ptr<OBB> myobb;
	std::shared_ptr<AABB> myAABB;

	bool imstatic;
	bool effected;

	int GetType() const { return TypeID; };
};

class damagedelt : public ACC::component
{

public:

	static const int TypeID = 11;

	float damage;

	int GetType() const { return TypeID; };
}; 

class attackspeedcomp : public ACC::component
{

public:

	static const int TypeID = 12;

	float attackspeed;
	float currectattacktime;

	int GetType() const { return TypeID; };
};

class velocitycomp : public ACC::component
{

public:

	static const int TypeID = 13;

	glm::vec3 velocity;

	int GetType() const { return TypeID; };
};

class bulletcomp : public ACC::component
{

public:

	static const int TypeID = 14;

	unsigned long int owner;

	int GetType() const { return TypeID; };
};


class crosshaircomp : public ACC::component
{

public:

	static const int TypeID = 15;

	int GetType() const { return TypeID; };
};

class namecomp : public ACC::component
{

public:

	static const int TypeID = 16;

	std::string myname;

	int GetType() const { return TypeID; };
};

class menucomp : public ACC::component
{

public:

	static const int TypeID = 17;

	enum menutype { quit, play, backtomain };

	menutype mytype;

	int GetType() const { return TypeID; };

};