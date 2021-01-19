#pragma once

#include <glm/glm.hpp>

class Triangle
{
public:
	Triangle();
	Triangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3);

	glm::vec3 v1;
	glm::vec3 v2;
	glm::vec3 v3;
};
