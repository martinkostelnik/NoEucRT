#pragma once

#include <glm/glm.hpp>
#include "Triangle.hpp"

class Ray
{
public:
	Ray();
	Ray(const glm::vec4& direction);

	glm::vec4 origin;
	glm::vec4 direction;

	bool intersectsTriangle(const Triangle& triangle, float& out_distance) const;
};
