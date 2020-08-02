#include "Resourcemanager.h"

Resourecmanager & Resourecmanager::instance() //get instance of our resource manager 
{
	static Resourecmanager myinstance;

	return myinstance;
}

std::shared_ptr<shader> Resourecmanager::getfromshadholder(std::string name) //get a shader 
{
	return shadholder.getshader(name);
}

std::shared_ptr<model> Resourecmanager::getfrommodelholder(std::string name) //get a model 
{
	return modholder.getmode(name);
}

AABB Resourecmanager::getAABB(std::string name) //get the aabb data for a model
{
	return modholder.getAABB(name);
}

OBB Resourecmanager::getOBB(std::string name) //get the obb data for a model
{
	return modholder.getOBB(name);
}

void Resourecmanager::addshader(std::shared_ptr<shader> newshader, std::string name) //add a new shader to the shader holder 
{
	shadholder.addshader(newshader, name);

}

void Resourecmanager::addmodels(std::string modelpath, std::string modelname) //add a normal model
{
	modholder.addmodel(modelpath, modelname);
}


void Resourecmanager::addskybox(std::vector<std::string> cube, std::string modelpath, std::string modelname) //add a skybox model
{
	modholder.addskybox(modelpath, cube, modelname);
}

void Resourecmanager::modelsinit() //create all of our models that we might need 
{
	addmodels("models/Main_charactor/mainguy.obj","mainguy");
	addmodels("models/enemies/enemy.obj", "enemy");
	addmodels("models/walls/Wall.obj", "wall");
	addmodels("models/floor/floor.obj", "floor");
	addmodels("models/bullet/bullet.obj", "bullet");
	addmodels("models/Crosshair/crosshair.obj", "crosshair");
	addmodels("models/PlayButton/playbutton.obj", "playbutton");
	addmodels("models/QuitButton/QuitButton.obj", "quitbutton");
	addmodels("models/BacktoMenu/BackToMenu.obj", "back");
	addmodels("models/Mazeofdeath/mazeofdeath.obj", "mazeofdeath");
	addmodels("models/Died/diedtext.obj", "death");

	std::vector<std::string> cube;
	cube.push_back("skyboximages/right.bmp");
	cube.push_back("skyboximages/left.bmp");
	cube.push_back("skyboximages/up.bmp");
	cube.push_back("skyboximages/down.bmp");
	cube.push_back("skyboximages/back.bmp");
	cube.push_back("skyboximages/front.bmp");
	addskybox(cube, "models/Skybox/skybox.obj","skybox");

}

void Resourecmanager::shaderinit() //create all of our shaders that we might need 
{
	std::shared_ptr<shader> skybox;
	skybox = std::make_shared<shader>();
	skybox->loadshader("shaders//skyboxvertex.txt", GL_VERTEX_SHADER);
	skybox->loadshader("shaders//skyboxfragment.txt", GL_FRAGMENT_SHADER);
	skybox->linkshader();
	skybox->linkcheck();
	addshader(skybox, "skyboxshader");

	std::shared_ptr<shader> justtexture;
	justtexture = std::make_shared<shader>();
	justtexture->loadshader("shaders//vertexshader.txt", GL_VERTEX_SHADER);
	justtexture->loadshader("shaders//fragmentshader.txt", GL_FRAGMENT_SHADER);
	justtexture->linkshader();
	justtexture->linkcheck();
	addshader(justtexture, "textureshader");

	std::shared_ptr<shader> crosshairshader;
	justtexture = std::make_shared<shader>();
	justtexture->loadshader("shaders//vertexshaderalpha.txt", GL_VERTEX_SHADER);
	justtexture->loadshader("shaders//fragmentshaderalpha.txt", GL_FRAGMENT_SHADER);
	justtexture->linkshader();
	justtexture->linkcheck();
	addshader(justtexture, "crosshairshad");

	std::shared_ptr<shader> lightshader;
	justtexture = std::make_shared<shader>();
	justtexture->loadshader("shaders//vertexshadertexture_lights.txt", GL_VERTEX_SHADER);
	justtexture->loadshader("shaders//fragmentshadertexture_Lights.txt", GL_FRAGMENT_SHADER);
	justtexture->linkshader();
	justtexture->linkcheck();
	addshader(justtexture, "lightshader");


	std::shared_ptr<shader> textshader;
	justtexture = std::make_shared<shader>();
	justtexture->loadshader("shaders//TextVertex.txt", GL_VERTEX_SHADER);
	justtexture->loadshader("shaders//TextFragment.txt", GL_FRAGMENT_SHADER);
	justtexture->linkshader();
	justtexture->linkcheck();
	addshader(justtexture, "textshader");

}


