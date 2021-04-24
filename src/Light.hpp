/**
 * @file Light.hpp
 * @author Martin Kostelník (xkoste12@stud.fit.vutbr.cz)
 * @brief Declaration file of the Light class, which is used to simulate lightning in the scene together with shaders.
 * @version 1.0
 * @date 2021-05-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include <glm/glm.hpp>

class Light
{
public:
	enum class Type
	{
		Distant,
		Point
	};

	Light(const glm::vec4 position, const float intensity, const glm::vec3 color, const Type type);

	const glm::vec4 position;
	const float intensity;
	const glm::vec3 color;
	const Type type;
};
