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

class Material
{
public:
	Material(const glm::vec3 albedo);
	glm::vec3 albedo;

	Material(const glm::vec3 albedo, const float shininess, const float ks, const float kd, const float ka);
	float shininess;
	float ka;
	float kd;
	float ks;
};
