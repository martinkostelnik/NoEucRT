#pragma once

#include <glm/glm.hpp>

class Camera
{
public:
	Camera();

	float fov;
	glm::mat4 toWorld;
};
