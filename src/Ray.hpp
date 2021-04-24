/**
 * @file Ray.hpp
 * @author Martin Kostelník (xkoste12@stud.fit.vutbr.cz)
 * @brief Declaration file of the Ray class. Rays are the core of the ray-tracing method and
 * they are also used in collision-detection.
 * @version 1.0
 * @date 2021-05-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include <glm/glm.hpp>

#include "Triangle.hpp"
#include "AABB.hpp"
#include "Light.hpp"
#include "Scene.hpp"

class Ray
{
public:
	Ray();
	Ray(const glm::vec4& direction);
	Ray(const glm::vec4& origin, const glm::vec4& direction);

	glm::vec4 origin;
	glm::vec4 direction;

	bool intersectsTriangle(const Triangle& triangle, float& out_distance) const;
	bool intersectsAABB(const AABB& aabb, float* const out_distance = nullptr) const;
	bool seesLight(const Light& light, const Scene& scene) const;
};
