#pragma once

#include <glm/glm.hpp>
#include "Triangle.hpp"
#include "AABB.hpp"

class Ray
{
public:
	Ray();
	Ray(const glm::vec4& direction);

	glm::vec4 origin;
	glm::vec4 direction;

	bool intersectsTriangle(const Triangle& triangle, float& out_distance) const;
	bool intersectsAABB(const AABB& aabb) const;
};
