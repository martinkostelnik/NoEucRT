#pragma once
#include <glm/glm.hpp>

class Light
{
public:
	Light();
	Light(const glm::vec3 position, const float intensity);
	Light(const glm::vec3 position, const float intensity, const glm::vec3 color);

	const glm::vec3 position;
	const float intensity;
	const glm::vec3 color;
};