#pragma once

#include <glm/glm.hpp>

class Ray
{
public:
	Ray();

	glm::vec4 origin;
	glm::vec4 direction;
};
