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

/**
 * @brief This class represents rays thrown into the scene by the renderer.
 * 
 */
class Ray
{
public:
	Ray();
	Ray(const glm::vec4& direction);
	Ray(const glm::vec4& origin, const glm::vec4& direction);

	glm::vec4 origin;
	glm::vec4 direction;

	/**
	 * @brief Ray triangle intersection test.
	 * 
	 * @param triangle Tested triangle
	 * @param out_distance Out parameter, the distance of the collision.
	 * @param out_u Out parameter, texture coordinate.
	 * @param out_v Out parameter, texture coordinate.
	 * @return true if ray hit the triangle
	 * @return false if ray did not hit the triangle
	 */
	bool intersectsTriangle(const Triangle& triangle, float& out_distance, float* out_u = nullptr, float* out_v = nullptr) const;

	/**
	 * @brief Ray AAB intersection test.
	 * 
	 * @param aabb Tested AABB
	 * @param out_distance Out parameter, the distance of the collision
	 * @return true if ray hit the AABB
	 * @return false if ray did not hit the AABB
	 */
	bool intersectsAABB(const AABB& aabb, float* const out_distance = nullptr) const;

	/**
	 * @brief Test if the ray sees concrete light for creating shadows.
	 * 
	 * @param light Tested light
	 * @param scene Scene
	 * @return true if the ray's vision of the light is not obstructed
	 * @return false if the ray's vision of the light is obstructed
	 */
	bool seesLight(const Light& light, const Scene& scene) const;
};
