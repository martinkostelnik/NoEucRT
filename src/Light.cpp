#include "Light.hpp"

Light::Light() : 
	position(0.0f),
	intensity(255.0f),
	color(1.0f, 1.0f, 1.0f)
{
}

Light::Light(const glm::vec3 position, const float intensity) :
	position(position),
	intensity(intensity),
	color(1.0f, 1.0f, 1.0f)
{
}

Light::Light(const glm::vec3 position, const float intensity, const glm::vec3 color) :
	position(position),
	intensity(intensity),
	color(color)
{
}
