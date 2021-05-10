/**
 * @file Material.hpp
 * @author Martin Kostelník (xkoste12@stud.fit.vutbr.cz)
 * @brief Declaration file of the Material class. The class is used to grant material properties to objects.
 * @version 1.0
 * @date 2021-05-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once 

#include <glm/glm.hpp>
#include <string>

/**
 * @brief This class represents a material of an object.
 * 
 */
class Material
{
public:
	Material(const glm::vec3 albedo);
	Material(const glm::vec3 albedo, const float shininess, const float ks, const float kd, const float ka);

	/**
	 * @brief Loads material from a file with .mtl extension.
	 * 
	 * @param fileName Path to the file.
	 */
	void loadFromFile(const std::string fileName);

	/**
	 * @brief Color of an object normalized to <0, 1> values.
	 * 
	 */
	glm::vec3 albedo;

	/**
	 * @brief Shininnes in the Phong reflection model.
	 * 
	 */
	float shininess;

	/**
	 * @brief Ambient constant in the Phong reflection model.
	 * 
	 */
	float ka;

	/**
	 * @brief Diffuse constant in the Phong reflection model.
	 * 
	 */
	float kd;

	/**
	 * @brief Specular constant in the Phong reflection model.
	 * 
	 */
	float ks;
};
