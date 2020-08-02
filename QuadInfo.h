#pragma once
#include "OBB.h"
#include "AABB.h"
#include <memory>

// a small infomation struct for each collision entity to worry about

struct Quadinfo
{
	std::shared_ptr<OBB> objectobb;
	std::shared_ptr<AABB> objectaabb;
	bool cantmove;
	int unitID;

};
