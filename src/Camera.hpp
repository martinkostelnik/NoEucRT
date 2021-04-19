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
	glm::vec4 position;
	glm::vec4 lookAt;

	void reset();
	bool isInsideAABB(const AABB& aabb) const;
};
