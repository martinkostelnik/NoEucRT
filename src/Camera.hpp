#pragma once

#include <glm/glm.hpp>

class Camera
{
public:
	Camera();

	float fov;
	float speed;
	float Xrotation;
	glm::mat4 toWorld;
};
