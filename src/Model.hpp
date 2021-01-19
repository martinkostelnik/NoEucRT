#pragma once

#include <glm/glm.hpp>
#include <vector>

class Model
{
public:
	Model();

	std::vector<glm::vec3> vertices;
	std::vector<size_t> indices;
};
