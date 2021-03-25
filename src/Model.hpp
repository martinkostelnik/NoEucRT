#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <string>

#include "Triangle.hpp"
#include "AABB.hpp"
#include "Material.hpp"

class Model
{
public:
	Model();
	Model(const std::string fileName);

	void assembleTriangles();
	void constructBVH();
	void loadFromFile(std::string fileName);

	std::vector<glm::vec4> vertices;
	std::vector<glm::vec3> vertexNormals;
	std::vector<size_t> indices;

	glm::mat4 toWorld;
	
	Material material;

	std::vector<Triangle> triangles;
	AABB boundingBox;
};
