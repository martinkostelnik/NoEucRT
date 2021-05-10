/**
 * @file AABB.hpp
 * @author Martin Kostelník (xkoste12@stud.fit.vutbr.cz)
 * @brief Declaration file of the AABB class. This class Declares the AABB class, which is used
 * as a wrapper for objects to simplify calculations and save computation time.
 * @version 1.0
 * @date 2021-05-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include <glm/glm.hpp>

/**
 * @brief This class describes an axis aligned bounding box, which is wrapped around an object.
 * 
 */
class AABB
{
public:
	AABB();

	/**
	 * @brief The min point of the bounding box.
	 * 
	 */
	glm::vec3 min;

	/**
	 * @brief The max point of the bounding box.
	 * 
	 */
	glm::vec3 max;
};
