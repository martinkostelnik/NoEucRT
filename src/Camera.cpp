#include "Camera.hpp"

Camera::Camera()
{
	fov = 90;

	toWorld = glm::mat4(1.0f);
}
