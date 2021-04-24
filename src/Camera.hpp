/**
 * @file Camera.hpp
 * @author Martin Kostelník (xkoste12@stud.fit.vutbr.cz)
 * @brief Declaration file of the Camera class. This class declares Camera, which is used
 * as a player avatar and as a viewpoint into the scene.
 * @version 1.0
 * @date 2021-05-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

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
