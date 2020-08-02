#pragma once

#include "shaderholder.h"
#include "modelholder.h"

//our resource manager for all shaders,models and textures. 

class Resourecmanager
{
private:
	shaderholder shadholder;
	modelholder modholder;

public:

	static Resourecmanager &instance();

	std::shared_ptr<shader> getfromshadholder(std::string name);
	std::shared_ptr<model> getfrommodelholder(std::string name);
	AABB getAABB (std::string name);
	OBB getOBB(std::string name);


	void addshader(std::shared_ptr<shader> newshader,std::string name);
	void addmodels(std::string modelpath, std::string modelname);
	void addskybox(std::vector<std::string> cube, std::string modelpath, std::string modelname);

	void modelsinit();
	void shaderinit();


};