#include "Light.hpp"

Light::Light(const glm::vec3 position, const float intensity, const glm::vec3 color, const Type type) :
	position(position),
	intensity(intensity),
	color(color),
	type(type)
{
}
