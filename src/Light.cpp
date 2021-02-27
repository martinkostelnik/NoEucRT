#include "Light.hpp"

Light::Light() : 
	position(0.0f),
	intensity(0.0f)
{
}

Light::Light(const glm::vec3 position, const float intensity) :
	position(position),
	intensity(intensity)
{
}
