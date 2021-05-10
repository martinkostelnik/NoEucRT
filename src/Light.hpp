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

/**
 * @brief This class describes the representation of lights inside the scene.
 * 
 */
class Light
{
public:
	/**
	 * @brief A light can be either distant or represented by a point in space.
	 * 
	 */
	enum class Type
	{
		Distant,
		Point
	};

	Light(const glm::vec4 position, const float intensity, const glm::vec3 color, const Type type);

	/**
	 * @brief Position of a point light or direction of a distant light.
	 * 
	 */
	const glm::vec4 position;

	/**
	 * @brief Intensity of the light
	 * 
	 */
	const float intensity;

	/**
	 * @brief Color of the light
	 * 
	 */
	const glm::vec3 color;

	/**
	 * @brief Type
	 * 
	 */
	const Type type;
};
