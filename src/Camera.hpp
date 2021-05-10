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

/**
 * @brief This class desribes the camera, or, the user's avatar inside the scene.
 * 
 */
class Camera
{
public:
	Camera();

	/**
	 * @brief Field of view.
	 * 
	 */
	float fov;

	/**
	 * @brief Speed of the camera in units traveled per second.
	 * 
	 */
	float speed;

	/**
	 * @brief Current rotation around x axis.
	 * 
	 */
	float Xrotation;

	/**
	 * @brief Transformation matrix to the world coordinate system.
	 * 
	 */
	glm::mat4 toWorld;
	
	/**
	 * @brief Current position in the world coordinate system.
	 * 
	 */
	glm::vec4 position;

	/**
	 * @brief Current lookAt vector in the world coordinate system.
	 * 
	 */
	glm::vec4 lookAt;

	/**
	 * @brief Resets the camera to the default position with default values.
	 * 
	 */
	void reset();

	/**
	 * @brief Tests if the camera is inside an AABB of an object.
	 * 
	 * @param aabb The examined bounding box.
	 * @return true 
	 * @return false 
	 */
	bool isInsideAABB(const AABB& aabb) const;
};
