/**
 * @file Model.Hpp
 * @author Martin Kostelník (xkoste12@stud.fit.vutbr.cz)
 * @brief Declaration file of the Model class. Instances of this class represent 3D objects in the scene.
 * @version 1.0
 * @date 2021-05-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

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
		WarpedTunnel,
		RotationTunnel,
		ShrinkTunnel
	};

	Model();
	Model(const Type type);
	Model(const std::string fileName);

	void assembleTriangles();
	void buildAABB();
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
