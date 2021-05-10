/**
 * @file Camera.cpp
 * @author Martin Kostelník (xkoste12@stud.fit.vutbr.cz)
 * @brief Implementation file of the Camera class.
 * @version 1.0
 * @date 2021-05-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

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
	speed = 200.0f;
}

bool Camera::isInsideAABB(const AABB& aabb) const
{
	return (position.x >= aabb.min.x && position.x <= aabb.max.x) && 
		   (position.y >= aabb.min.y && position.y <= aabb.max.y) &&
		   (position.z >= aabb.min.z && position.z <= aabb.max.z);
}
