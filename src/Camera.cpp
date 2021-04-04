#include "Camera.hpp"

Camera::Camera() :
	fov(90.0),
	speed(200),
	toWorld(glm::mat4(1.0f)),
	Xrotation(0.0f),
	position(0.0f)
{
}

void Camera::reset()
{
	toWorld = glm::mat4(1.0f);
}

bool Camera::AABBCollision(const AABB& aabb) const
{
	return (position.x >= aabb.min.x && position.x <= aabb.max.x) &&
		   (position.y >= aabb.min.y && position.y <= aabb.max.y) &&
	       (position.z >= aabb.min.z && position.z <= aabb.max.z);
}
