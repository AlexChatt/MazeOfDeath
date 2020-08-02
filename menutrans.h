#pragma once
#include "component.h"

//menu trasition for the scenes

struct menutrans
{
	enum menutype { quit, play, backtomain};

	menutype changetype;
	bool change;

	menutrans()
	{
		change = false;
	}

};
