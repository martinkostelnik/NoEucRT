#pragma once

#include <glm/glm.hpp>

#include "AABB.hpp"

class Camera
{
public:
	Camera();

	float fov;
	float speed;
	float Xrotation;

	glm::mat4 toWorld;
	glm::vec3 position;

	void reset();
	bool AABBCollision(const AABB& aabb) const;
};
