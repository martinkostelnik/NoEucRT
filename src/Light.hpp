#pragma once
#include <glm/glm.hpp>

class Light
{
public:
	Light();
	Light(const glm::vec3 position, const float intensity);

private:
	const glm::vec3 position;
	const float intensity;
};
