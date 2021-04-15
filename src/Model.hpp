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
	enum class Type
	{
		Euclidean,
		Portal,
		WarpedTunnel
	};

	Model();
	Model(const Type type);
	Model(const std::string fileName);

	void assembleTriangles();
	void constructBVH();
	void loadFromFile(const std::string fileName);

	std::vector<glm::vec4> vertices;
	std::vector<glm::vec3> vertexNormals;
	std::vector<size_t> indices;

	glm::mat4 toWorld;
	
	Material material;

	std::vector<Triangle> triangles;
	AABB boundingBox;

	Type type;
};
