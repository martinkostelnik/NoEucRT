#pragma once

#include <glm/glm.hpp>
#include <vector>

#include "Triangle.hpp"

class Model
{
public:
	Model();
	void assembleTriangles();

	std::vector<glm::vec4> vertices;
	std::vector<size_t> indices;

	std::vector<Triangle> triangles;
};
