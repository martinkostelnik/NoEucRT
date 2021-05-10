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

#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>
#include <vector>
#include <map>
#include <string>

#include "Triangle.hpp"
#include "AABB.hpp"
#include "Material.hpp"

/**
 * @brief This class is used to represent an object inside the scene.
 * 
 */
class Model
{
public:
	/**
	 * @brief Describes whether an object is euclidean or non-euclidean.
	 * 
	 */
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

	/**
	 * @brief Primitive assembly,
	 * 
	 */
	void assembleTriangles();

	/**
	 * @brief Bounding box construction.
	 * 
	 */
	void buildAABB();

	/**
	 * @brief Load object from a .obj file.
	 * 
	 * @param fileName Path to the .obj file.
	 */
	void loadFromFile(const std::string fileName);


	std::vector<glm::vec4> vertices;
	std::vector<glm::vec2> textureCoordinates;
	std::vector<size_t> indices;

	/**
	 * @brief This associates a texture coordinate to each vertex.
	 * 
	 */
	std::map<const glm::vec4*, const glm::vec2*> textureCoordinateMapping;

	/**
	 * @brief Transformation matrix to the world coordinate system.
	 * 
	 */
	glm::mat4 toWorld;
	
	/**
	 * @brief Material of the object.
	 * 
	 */
	Material material;
	
	sf::Image texture;
	std::vector<Triangle> triangles;
	AABB boundingBox;

	Type type;
};
