#pragma once

#include <glm/glm.hpp>

class Camera
{
public:
	Camera();

	float fov;
	float speed;
	glm::mat4 toWorld;
};
