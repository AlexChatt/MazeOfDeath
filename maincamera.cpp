#include "maincamera.h"

maincamera::maincamera()
{
	View = glm::mat4(1.0);
}

void maincamera::setProjection(glm::mat4 &proj)
{
	Projection = proj;
}

void maincamera::setView()
{
	View = glm::lookAt(playertrans->position + glm::vec3(5, 15, 0.0), playertrans->position, glm::vec3(0, 1, 0)); //setupmain cam for player 
	position = playertrans->position + glm::vec3(5, 15, 0.0);
}

void maincamera::setView(glm::mat4 &setview) //personalsetup for cam
{
	View = setview;
}

void maincamera::setposition(glm::vec3 campos)
{
	position = campos;
		
}

void maincamera::setdirection(glm::vec3 dir)
{
	direction = dir;

}
