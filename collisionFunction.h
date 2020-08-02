#pragma once

#include "AABB.h"
#include "OBB.h"
#include <glm.hpp>

//overall collison functions that i may need

bool rayplanecollion(glm::vec3 raypos, glm::vec3 raydir, glm::vec3 boxmax, glm::vec3 boxmin);

glm::vec3 rayplanecollionvec(glm::vec3 raypos, glm::vec3 raydir, glm::vec3 boxmax, glm::vec3 boxmin);