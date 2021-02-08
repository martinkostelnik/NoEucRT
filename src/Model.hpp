#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <string>

#include "Triangle.hpp"
#include "AABB.hpp"

class Model
{
public:
	Model();
	Model(const std::string fileName);

	void assembleTriangles();
	void loadFromFile(std::string fileName);

	std::vector<glm::vec4> vertices;
	std::vector<size_t> indices;
	glm::mat4 toWorld;

	std::vector<Triangle> triangles;
	AABB boundingBox;
};
