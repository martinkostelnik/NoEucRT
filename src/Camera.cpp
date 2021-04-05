#include "Camera.hpp"

Camera::Camera() :
	fov(90.0),
	speed(200),
	toWorld(glm::mat4(1.0f)),
	Xrotation(0.0f),
	position(0.0f, 0.0f, 0.0f, 1.0f),
	lookAt(0.0f, 0.0f, -1.0f, 0.0f)
{
}

void Camera::reset()
{
	toWorld = glm::mat4(1.0f);
	Xrotation = 0.0f;
	position = { 0.0f, 0.0f, 0.0f, 1.0f };
	lookAt = { 0.0f, 0.0f, -1.0f, 0.0f };
}
