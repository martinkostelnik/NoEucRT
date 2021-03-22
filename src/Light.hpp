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

	Light(const glm::vec3 position, const float intensity, const glm::vec3 color, const Type type);

	const glm::vec3 position;
	const float intensity;
	const glm::vec3 color;
	const Type type;
};
