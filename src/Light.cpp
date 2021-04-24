/**
 * @file Light.cpp
 * @author Martin Kostelník (xkoste12@stud.fit.vutbr.cz)
 * @brief Implementation file of the Light class.
 * @version 1.0
 * @date 2021-05-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "Light.hpp"

Light::Light(const glm::vec4 position, const float intensity, const glm::vec3 color, const Type type) :
	position(position),
	intensity(intensity),
	color(color),
	type(type)
{
}
