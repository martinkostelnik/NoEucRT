/**
 * @file Triangle.hpp
 * @author Martin Kostelník (xkoste12@stud.fit.vutbr.cz)
 * @brief Declaration file of the Triangle class. Objects are composed of meshes of these triangles.
 * @version 1.0
 * @date 2021-05-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include <glm/glm.hpp>

/**
 * @brief This class represents a triangle of an object.
 * 
 */
class Triangle
{
public:
	Triangle(const glm::vec4& v1, const glm::vec4& v2, const glm::vec4& v3);

	const glm::vec4& v1;
	const glm::vec4& v2;
	const glm::vec4& v3;
};
