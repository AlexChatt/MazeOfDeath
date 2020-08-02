#pragma once

#include <SDL.h>
#include <vector>
#include "keystruct.h"

//a singleton input logger for tracking inputs from the mouse and keyboard

class inputlogger
{
private:
	int mousex;
	int mousey;
	bool leftmouseup;
	bool rightmouseup;
	std::vector<keystruct> mykeys;
	SDL_Event incomingEvent;

public:

	inputlogger();
	static inputlogger &instance();
	void update(bool &go);
	void createkeylog(int key);
	bool getkeyup(int key);
	bool getkeydown(int key);
	bool getleftmouse();

	int getmousex()
	{
		return mousex;
	}
	int getmousey()
	{
		return mousey;
	}
};