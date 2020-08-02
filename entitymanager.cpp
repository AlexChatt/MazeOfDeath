#include "entitymanager.h"

//we assign components to our needed entities 

entitymanager::entitymanager()
{
	
}

void entitymanager::delete_entity()
{
	entities.clear();
	tooadd.clear();
	todelete.clear();


}

void entitymanager::create_skybox() //create a skybox
{
	std::shared_ptr<ACC::entity> skyboxcomp;
	skyboxcomp = std::make_shared<ACC::entity>(IDs.getID());
	std::shared_ptr<transposecomponent> skytrans;
	skytrans = std::make_shared<transposecomponent>();
	skytrans->position = glm::vec3(0,0,0);
	skytrans->up = glm::vec3(0, 1, 0);
	skytrans->right = glm::vec3(1, 0, 0);
	skytrans->forward = glm::vec3(0, 0, 1);
	skytrans->scale = glm::vec3(1, 1, 1);
	skyboxcomp->addcomponent(skytrans);

	std::shared_ptr<modelcomponent> skymod;
	skymod = std::make_shared<modelcomponent>();
	skymod->myshader = Resourecmanager::instance().getfromshadholder("skyboxshader");
	skymod->mymodel = Resourecmanager::instance().getfrommodelholder("skybox");
	skymod->drawme = true;
	skymod->depth = true;
	skymod->myshine = 1.0;
	skymod->mystrenght = 1.0;
	skymod->effectedbylights = false;
	skyboxcomp->addcomponent(skymod);

	entities[skyboxcomp->returnID()] = skyboxcomp;
	tooadd.push_back(skyboxcomp);
}

void entitymanager::create_directionlight(std::shared_ptr<dirlight> mydirinfo) //create a directional light
{
	std::shared_ptr<ACC::entity> dirlight = std::make_shared<ACC::entity>(IDs.getID());

	std::shared_ptr<lightcomp> entlight = std::make_shared<lightcomp>();
	
	entlight->mylight = mydirinfo;
	dirlight->addcomponent(entlight);

	std::shared_ptr<namecomp> myname = std::make_shared<namecomp>();
	myname->myname = "dirlight";
	dirlight->addcomponent(myname);

	entities[dirlight->returnID()] = dirlight;
	tooadd.push_back(dirlight);

}

void entitymanager::createflashlight(std::shared_ptr<ACC::entity> parent) //create a flashlight
{ 
	std::shared_ptr<ACC::entity> spotl = std::make_shared<ACC::entity>(IDs.getID());

	std::shared_ptr<spotlight> myspotlight = std::make_shared<spotlight>();
	myspotlight->setamb(glm::vec3(1.0, 0, 0));
	myspotlight->setlightcolour(glm::vec3(1.0f,0.0,0.0));
	myspotlight->setconstant(1.0f);
	myspotlight->setdir(glm::vec3(0, 0, 1));
	myspotlight->setlinear(0.045f);
	myspotlight->setquadratic(0.0075f);
	myspotlight->setpos(glm::vec3(0,0,1));
	myspotlight->setrad(glm::cos(glm::radians(16.5f)));
	myspotlight->settouterrad(glm::cos(glm::radians(60.5f)));

	std::shared_ptr<animationholdercomp> imapart = std::make_shared<animationholdercomp>();
	imapart->myowner = parent;
	imapart->offset = glm::vec3(0, 1, 0);
	imapart->mytype = imapart->light;
	spotl->addcomponent(imapart);


	std::shared_ptr<lightcomp> entlight = std::make_shared<lightcomp>();
	entlight->mylight = myspotlight;
	spotl->addcomponent(entlight);

	std::shared_ptr<namecomp> myname = std::make_shared<namecomp>();
	myname->myname = "flashlight";
	spotl->addcomponent(myname);

	entities[spotl->returnID()] = spotl;
	tooadd.push_back(spotl);
}


std::shared_ptr<ACC::entity> entitymanager::createPlayer(glm::vec3 pos, std::shared_ptr<transposecomponent> playtrans) //create our player
{
	std::shared_ptr<ACC::entity> playerent;
	playerent = std::make_shared<ACC::entity>(IDs.getID());
	std::shared_ptr<transposecomponent> playertrans;
	playertrans = std::make_shared<transposecomponent>();
	playertrans->position = pos;
	playertrans->up = glm::vec3(0, 1, 0);
	playertrans->right = glm::vec3(1, 0, 0);
	playertrans->forward = glm::vec3(0, 0, 1);
	playertrans->scale = glm::vec3(1, 1, 1);
	playerent->addcomponent(playertrans);

	playtrans = playertrans;

	std::shared_ptr<modelcomponent> playermod;
	playermod = std::make_shared<modelcomponent>();
	playermod->myshader = Resourecmanager::instance().getfromshadholder("lightshader");
	playermod->mymodel = Resourecmanager::instance().getfrommodelholder("mainguy");
	playermod->drawme = true;
	playermod->depth = true;
	playermod->myshine = 1.0;
	playermod->mystrenght = 1.0;
	playermod->effectedbylights = true;
	playerent->addcomponent(playermod);

	std::shared_ptr<playercomp> iamplayer = std::make_shared<playercomp>();
	playerent->addcomponent(iamplayer);

	std::shared_ptr<speedcomp> playerspeed = std::make_shared<speedcomp>();
	playerspeed->speed = 5;
	playerent->addcomponent(playerspeed);

	std::shared_ptr<directioncomponent> playerdir = std::make_shared<directioncomponent>();
	playerdir->newdirect = glm::vec3(0, 0, 1);
	playerdir->direction = glm::vec3(0, 0, 1);
	playerent->addcomponent(playerdir);

	std::shared_ptr<attackspeedcomp> playyerattackspeed = std::make_shared<attackspeedcomp>();
	playyerattackspeed->currectattacktime = 1;
	playyerattackspeed->attackspeed = 0.2;
	playerent->addcomponent(playyerattackspeed);

	std::shared_ptr<collisioncomp> playercol = std::make_shared<collisioncomp>();
	playercol->imstatic = false;
	playercol->myAABB = std::make_shared<AABB>(Resourecmanager::instance().getAABB("mainguy"));
	playercol->myobb = std::make_shared<OBB>(Resourecmanager::instance().getOBB("mainguy"));
	playercol->myAABB->update(glm::quat(), pos);
	playercol->myobb->update(pos, glm::quat());
	playercol->effected = false;
	playerent->addcomponent(playercol);

	std::shared_ptr<velocitycomp> playervel = std::make_shared<velocitycomp>();
	playervel->velocity = glm::vec3(0, 0, 0);
	playerent->addcomponent(playervel);

	std::shared_ptr<healthcomponent> playerhealth = std::make_shared<healthcomponent>();
	playerhealth->maxhp = 100;
	playerhealth->health = 100;
	playerhealth->hitdelete = false;
	playerent->addcomponent(playerhealth);

	createflashlight(playerent);

	entities[playerent->returnID()] = playerent;
	tooadd.push_back(playerent);

	std::shared_ptr<namecomp> myname = std::make_shared<namecomp>();
	myname->myname = "player";
	playerent->addcomponent(myname);

	return playerent;
}

void entitymanager::createEnemy(glm::vec3 pos) //create an enemy for the game
{
	std::shared_ptr<ACC::entity> enemyent;
	enemyent = std::make_shared<ACC::entity>(IDs.getID());
	std::shared_ptr<transposecomponent> enmeytrans;
	enmeytrans = std::make_shared<transposecomponent>();
	enmeytrans->position = pos;
	enmeytrans->up = glm::vec3(0, 1, 0);
	enmeytrans->right = glm::vec3(1, 0, 0);
	enmeytrans->forward = glm::vec3(0, 0, 1);
	enmeytrans->scale = glm::vec3(1, 1, 1);
	enemyent->addcomponent(enmeytrans);

	std::shared_ptr<modelcomponent> enemymod;
	enemymod = std::make_shared<modelcomponent>();
	enemymod->myshader = Resourecmanager::instance().getfromshadholder("lightshader");
	enemymod->mymodel = Resourecmanager::instance().getfrommodelholder("enemy");
	enemymod->drawme = true;
	enemymod->depth = true;
	enemymod->myshine = 1.0;
	enemymod->mystrenght = 1.0;
	enemymod->effectedbylights = true;
	enemyent->addcomponent(enemymod);

	std::shared_ptr<speedcomp> enemyspeed = std::make_shared<speedcomp>();
	enemyspeed->speed = 4;
	enemyent->addcomponent(enemyspeed);

	std::shared_ptr<directioncomponent> enemydir = std::make_shared<directioncomponent>();
	enemydir->newdirect = glm::vec3(0, 0, 1);
	enemydir->direction = glm::vec3(0, 0, 1);
	enemyent->addcomponent(enemydir);

	std::shared_ptr<AIcomp> enemyisAI = std::make_shared<AIcomp>();
	enemyisAI->mystate = enemyisAI->idel;
	enemyisAI->recaltime = 10;
	enemyent->addcomponent(enemyisAI);

	std::shared_ptr<damagedelt> enemeydamage = std::make_shared<damagedelt>();
	enemeydamage->damage = 1;
	enemyent->addcomponent(enemeydamage);

	std::shared_ptr<healthcomponent> enemyhealth = std::make_shared<healthcomponent>();
	enemyhealth->maxhp = 50;
	enemyhealth->health = 50;
	enemyhealth->hitdelete = false;
	enemyent->addcomponent(enemyhealth);

	std::shared_ptr<collisioncomp> enemycol = std::make_shared<collisioncomp>();
	enemycol->imstatic = false;
	enemycol->myAABB = std::make_shared<AABB>(Resourecmanager::instance().getAABB("enemy"));
	enemycol->myobb = std::make_shared<OBB>(Resourecmanager::instance().getOBB("enemy"));
	enemycol->myAABB->update(glm::quat(), pos);
	enemycol->myobb->update(pos, glm::quat());
	enemycol->effected = false;
	enemyent->addcomponent(enemycol);

	std::shared_ptr<velocitycomp> enemyvel = std::make_shared<velocitycomp>();
	enemyvel->velocity = glm::vec3(0, 0, 0);
	enemyent->addcomponent(enemyvel);

	std::shared_ptr<namecomp> myname = std::make_shared<namecomp>();
	myname->myname = "enemy";
	enemyent->addcomponent(myname);

	entities[enemyent->returnID()] = enemyent;
	tooadd.push_back(enemyent);

}

void entitymanager::createFloor(glm::vec3 pos) //create a floor tile
{
	std::shared_ptr<ACC::entity> floorent;
	floorent = std::make_shared<ACC::entity>(IDs.getID());
	std::shared_ptr<transposecomponent> floortrans;
	floortrans = std::make_shared<transposecomponent>();
	floortrans->position = pos;
	floortrans->up = glm::vec3(0, 1, 0);
	floortrans->right = glm::vec3(1, 0, 0);
	floortrans->forward = glm::vec3(0, 0, 1);
	floortrans->scale = glm::vec3(1, 1, 1);
	floorent->addcomponent(floortrans);

	std::shared_ptr<modelcomponent> floormod;
	floormod = std::make_shared<modelcomponent>();
	floormod->myshader = Resourecmanager::instance().getfromshadholder("lightshader");
	floormod->mymodel = Resourecmanager::instance().getfrommodelholder("floor");
	floormod->drawme = true;
	floormod->myshine = 1.0;
	floormod->mystrenght = 1.0;
	floormod->depth = true;
	floormod->effectedbylights = true;
	floorent->addcomponent(floormod);

	std::shared_ptr<namecomp> myname = std::make_shared<namecomp>();
	myname->myname = "floor";
	floorent->addcomponent(myname);

	entities[floorent->returnID()] = floorent;
	tooadd.push_back(floorent);
}

void entitymanager::createWall(glm::vec3 pos)
{
	std::shared_ptr<ACC::entity> wallent;
	wallent = std::make_shared<ACC::entity>(IDs.getID());
	std::shared_ptr<transposecomponent> walltrans;
	walltrans = std::make_shared<transposecomponent>();
	walltrans->position = pos;
	walltrans->up = glm::vec3(0, 1, 0);
	walltrans->right = glm::vec3(1, 0, 0);
	walltrans->forward = glm::vec3(0, 0, 1);
	walltrans->scale = glm::vec3(1, 1, 1);
	wallent->addcomponent(walltrans);

	std::shared_ptr<modelcomponent> wallmod;
	wallmod = std::make_shared<modelcomponent>();
	wallmod->myshader = Resourecmanager::instance().getfromshadholder("lightshader");
	wallmod->mymodel = Resourecmanager::instance().getfrommodelholder("wall");
	wallmod->drawme = true;
	wallmod->depth = true;
	wallmod->myshine = 1.0;
	wallmod->mystrenght = 1.0;
	wallmod->effectedbylights = true;
	wallent->addcomponent(wallmod);

	std::shared_ptr<collisioncomp> wallcoll = std::make_shared<collisioncomp>();
	wallcoll->imstatic = true;
	wallcoll->myAABB = std::make_shared<AABB>(Resourecmanager::instance().getAABB("wall"));
	wallcoll->myobb = std::make_shared<OBB>(Resourecmanager::instance().getOBB("wall"));
	wallcoll->myAABB->update(glm::quat(), pos);
	wallcoll->myobb->update(pos, glm::quat());
	wallcoll->effected = false;
	wallent->addcomponent(wallcoll);

	std::shared_ptr<namecomp> myname = std::make_shared<namecomp>();
	myname->myname = "wall";
	wallent->addcomponent(myname);

	entities[wallent->returnID()] = wallent;
	tooadd.push_back(wallent);

}

void entitymanager::createbullet(glm::vec3 pos, glm::quat orin, unsigned long int ownerID) //create a bullet 
{
	std::shared_ptr<ACC::entity> bullet;
	bullet = std::make_shared<ACC::entity>(IDs.getID());
	std::shared_ptr<transposecomponent> bullettrans;
	bullettrans = std::make_shared<transposecomponent>();
	bullettrans->position = pos;
	bullettrans->myquat = orin;
	bullettrans->up = glm::vec3(0, 1, 0);
	bullettrans->right = glm::vec3(1, 0, 0);
	bullettrans->forward = glm::vec3(0, 0, 1);
	bullettrans->scale = glm::vec3(1, 1, 1);
	bullet->addcomponent(bullettrans);

	std::shared_ptr<modelcomponent> bulletmod;
	bulletmod = std::make_shared<modelcomponent>();
	bulletmod->myshader = Resourecmanager::instance().getfromshadholder("lightshader");
	bulletmod->mymodel = Resourecmanager::instance().getfrommodelholder("bullet");
	bulletmod->drawme = true;
	bulletmod->depth = true;
	bulletmod->myshine = 1.0;
	bulletmod->mystrenght = 1.0;
	bulletmod->effectedbylights = true;
	bullet->addcomponent(bulletmod);

	std::shared_ptr<collisioncomp> bulletcol = std::make_shared<collisioncomp>();
	bulletcol->myAABB = std::make_shared<AABB>(Resourecmanager::instance().getAABB("bullet"));
	bulletcol->myobb = std::make_shared<OBB>(Resourecmanager::instance().getOBB("bullet"));
	bulletcol->imstatic = false;
	bulletcol->myAABB->update(orin, pos);
	bulletcol->myobb->update(pos, orin);
	bulletcol->effected = true;
	bullet->addcomponent(bulletcol);

	std::shared_ptr<velocitycomp> bulletvel = std::make_shared<velocitycomp>();
	bulletvel->velocity = (orin *  glm::vec3(0, 0, 1)) * 20.0f;
	bullet->addcomponent(bulletvel);

	std::shared_ptr<bulletcomp> bulletowner = std::make_shared<bulletcomp>();
	bulletowner->owner = ownerID;
	bullet->addcomponent(bulletowner);

	std::shared_ptr<damagedelt> bulletdamage = std::make_shared<damagedelt>();
	bulletdamage->damage = 20;
	bullet->addcomponent(bulletdamage);

	std::shared_ptr<namecomp> myname = std::make_shared<namecomp>();
	myname->myname = "bullet";
	bullet->addcomponent(myname);

	entities[bullet->returnID()]= bullet;
	tooadd.push_back(bullet);

}

void entitymanager::createcrosshair(glm::vec3 pos) //create a crosshair
{
	std::shared_ptr<ACC::entity> crosshair;
	crosshair = std::make_shared<ACC::entity>(IDs.getID());
	std::shared_ptr<transposecomponent> crosstrans;
	crosstrans = std::make_shared<transposecomponent>();
	crosstrans->position = pos;
	crosstrans->up = glm::vec3(0, 1, 0);
	crosstrans->right = glm::vec3(1, 0, 0);
	crosstrans->forward = glm::vec3(0, 0, 1);
	crosstrans->scale = glm::vec3(1, 1, 1);
	crosshair->addcomponent(crosstrans);

	std::shared_ptr<modelcomponent> crossmodel;
	crossmodel = std::make_shared<modelcomponent>();
	crossmodel->myshader = Resourecmanager::instance().getfromshadholder("crosshairshad");
	crossmodel->mymodel = Resourecmanager::instance().getfrommodelholder("crosshair");
	crossmodel->drawme = true;
	crossmodel->effectedbylights = false;
	crossmodel->depth = false;
	crosshair->addcomponent(crossmodel);

	std::shared_ptr<crosshaircomp> iamcross = std::make_shared<crosshaircomp>();
	crosshair->addcomponent(iamcross);

	std::shared_ptr<namecomp> myname = std::make_shared<namecomp>();
	myname->myname = "crosshair";
	crosshair->addcomponent(myname);

	entities[crosshair->returnID()] = crosshair;
	tooadd.push_back(crosshair);
}

void entitymanager::createplaybutton(glm::vec3 pos) //create a play button
{
	std::shared_ptr<ACC::entity> playbutton;
	playbutton = std::make_shared<ACC::entity>(IDs.getID());

	std::shared_ptr<transposecomponent> playbuttontrans;
	playbuttontrans = std::make_shared<transposecomponent>();
	playbuttontrans->position = pos;
	playbuttontrans->up = glm::vec3(0, 1, 0);
	playbuttontrans->right = glm::vec3(1, 0, 0);
	playbuttontrans->forward = glm::vec3(0, 0, 1);
	playbuttontrans->scale = glm::vec3(1, 1, 1);
	playbutton->addcomponent(playbuttontrans);

	std::shared_ptr<modelcomponent> playbutmod;
	playbutmod = std::make_shared<modelcomponent>();
	playbutmod->myshader = Resourecmanager::instance().getfromshadholder("crosshairshad");
	playbutmod->mymodel = Resourecmanager::instance().getfrommodelholder("playbutton");
	playbutmod->drawme = true;
	playbutmod->effectedbylights = false;
	playbutmod->depth = true;
	playbutton->addcomponent(playbutmod);

	std::shared_ptr<collisioncomp> playbuttoncol = std::make_shared<collisioncomp>();
	playbuttoncol->myAABB = std::make_shared<AABB>(Resourecmanager::instance().getAABB("playbutton"));
	playbuttoncol->myobb = std::make_shared<OBB>(Resourecmanager::instance().getOBB("playbutton"));
	playbuttoncol->imstatic = false;
	playbuttoncol->myAABB->update(playbuttontrans->myquat, pos);
	playbuttoncol->myobb->update(pos, playbuttontrans->myquat);
	playbutton->addcomponent(playbuttoncol);

	std::shared_ptr<menucomp> mymenucomp = std::make_shared<menucomp>();
	mymenucomp->mytype = mymenucomp->play;
	playbutton->addcomponent(mymenucomp);

	entities[playbutton->returnID()] = playbutton;
	tooadd.push_back(playbutton);
}

void entitymanager::createbackbutton(glm::vec3 pos) //create a back button
{
	std::shared_ptr<ACC::entity> backbutton;
	backbutton = std::make_shared<ACC::entity>(IDs.getID());

	std::shared_ptr<transposecomponent> buttontrans;
	buttontrans = std::make_shared<transposecomponent>();
	buttontrans->position = pos;
	buttontrans->up = glm::vec3(0, 1, 0);
	buttontrans->right = glm::vec3(1, 0, 0);
	buttontrans->forward = glm::vec3(0, 0, 1);
	buttontrans->scale = glm::vec3(1, 1, 1);
	backbutton->addcomponent(buttontrans);

	std::shared_ptr<modelcomponent> butmod;
	butmod = std::make_shared<modelcomponent>();
	butmod->myshader = Resourecmanager::instance().getfromshadholder("crosshairshad");
	butmod->mymodel = Resourecmanager::instance().getfrommodelholder("back");
	butmod->drawme = true;
	butmod->effectedbylights = false;
	butmod->depth = true;
	backbutton->addcomponent(butmod);

	std::shared_ptr<collisioncomp> buttoncol = std::make_shared<collisioncomp>();
	buttoncol->myAABB = std::make_shared<AABB>(Resourecmanager::instance().getAABB("back"));
	buttoncol->myobb = std::make_shared<OBB>(Resourecmanager::instance().getOBB("back"));
	buttoncol->imstatic = false;
	buttoncol->myAABB->update(buttontrans->myquat, pos);
	buttoncol->myobb->update(pos, buttontrans->myquat);
	backbutton->addcomponent(buttoncol);

	std::shared_ptr<menucomp> mymenucomp = std::make_shared<menucomp>();
	mymenucomp->mytype = mymenucomp->backtomain;
	backbutton->addcomponent(mymenucomp);


	entities[backbutton->returnID()] = backbutton;
	tooadd.push_back(backbutton);
}

void entitymanager::createquitbutton(glm::vec3 pos) //create a quit button
{
	std::shared_ptr<ACC::entity> quitbutton;
	quitbutton = std::make_shared<ACC::entity>(IDs.getID());

	std::shared_ptr<transposecomponent> buttontrans;
	buttontrans = std::make_shared<transposecomponent>();
	buttontrans->position = pos;
	buttontrans->up = glm::vec3(0, 1, 0);
	buttontrans->right = glm::vec3(1, 0, 0);
	buttontrans->forward = glm::vec3(0, 0, 1);
	buttontrans->scale = glm::vec3(1, 1, 1);
	quitbutton->addcomponent(buttontrans);

	std::shared_ptr<modelcomponent> butmod;
	butmod = std::make_shared<modelcomponent>();
	butmod->myshader = Resourecmanager::instance().getfromshadholder("crosshairshad");
	butmod->mymodel = Resourecmanager::instance().getfrommodelholder("quitbutton");
	butmod->drawme = true;
	butmod->effectedbylights = false;
	butmod->depth = true;
	quitbutton->addcomponent(butmod);

	std::shared_ptr<collisioncomp> buttoncol = std::make_shared<collisioncomp>();
	buttoncol->myAABB = std::make_shared<AABB>(Resourecmanager::instance().getAABB("quitbutton"));
	buttoncol->myobb = std::make_shared<OBB>(Resourecmanager::instance().getOBB("quitbutton"));
	buttoncol->imstatic = false;
	buttoncol->myAABB->update(buttontrans->myquat, pos);
	buttoncol->myobb->update(pos, buttontrans->myquat);
	quitbutton->addcomponent(buttoncol);

	std::shared_ptr<menucomp> mymenucomp = std::make_shared<menucomp>();
	mymenucomp->mytype = mymenucomp->quit;
	quitbutton->addcomponent(mymenucomp);

	entities[quitbutton->returnID()] = quitbutton;
	tooadd.push_back(quitbutton);

}

void entitymanager::createMazeText(glm::vec3 pos) //create a mazetextbox 
{
	std::shared_ptr<ACC::entity> mazetext;
	mazetext = std::make_shared<ACC::entity>(IDs.getID());

	std::shared_ptr<transposecomponent> buttontrans;
	buttontrans = std::make_shared<transposecomponent>();
	buttontrans->position = pos;
	buttontrans->up = glm::vec3(0, 1, 0);
	buttontrans->right = glm::vec3(1, 0, 0);
	buttontrans->forward = glm::vec3(0, 0, 1);
	buttontrans->scale = glm::vec3(1, 1, 1);
	mazetext->addcomponent(buttontrans);

	std::shared_ptr<modelcomponent> butmod;
	butmod = std::make_shared<modelcomponent>();
	butmod->myshader = Resourecmanager::instance().getfromshadholder("crosshairshad");
	butmod->mymodel = Resourecmanager::instance().getfrommodelholder("mazeofdeath");
	butmod->drawme = true;
	butmod->effectedbylights = false;
	butmod->depth = true;
	mazetext->addcomponent(butmod);

	entities[mazetext->returnID()] = mazetext;
	tooadd.push_back(mazetext);
}

void entitymanager::createdeathtext(glm::vec3 pos) //create a death text box 
{
	std::shared_ptr<ACC::entity> deathtext;
	deathtext = std::make_shared<ACC::entity>(IDs.getID());

	std::shared_ptr<transposecomponent> buttontrans;
	buttontrans = std::make_shared<transposecomponent>();
	buttontrans->position = pos;
	buttontrans->up = glm::vec3(0, 1, 0);
	buttontrans->right = glm::vec3(1, 0, 0);
	buttontrans->forward = glm::vec3(0, 0, 1);
	buttontrans->scale = glm::vec3(1, 1, 1);
	deathtext->addcomponent(buttontrans);

	std::shared_ptr<modelcomponent> butmod;
	butmod = std::make_shared<modelcomponent>();
	butmod->myshader = Resourecmanager::instance().getfromshadholder("crosshairshad");
	butmod->mymodel = Resourecmanager::instance().getfrommodelholder("death");
	butmod->drawme = true;
	butmod->effectedbylights = false;
	butmod->depth = true;
	deathtext->addcomponent(butmod);

	entities[deathtext->returnID()] = deathtext;
	tooadd.push_back(deathtext);



}



void entitymanager::cleartodelete() //delete all entities we no longer need 
{
	for (int i = 0; i < todelete.size(); i++)
	{
		std::unordered_map<unsigned long int, std::shared_ptr<ACC::entity>>::const_iterator got = entities.find(todelete[i]->returnID());
		if (got != entities.end())
		{
			entities[todelete[i]->returnID()]->setdeleteme();
		}
		entities.erase(todelete[i]->returnID());
		todelete.erase(todelete.begin() + i);
		i--;
	}
	todelete.clear();
}