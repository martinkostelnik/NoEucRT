/**
 * @file Portal.hpp
 * @author Martin Kostelník (xkoste12@stud.fit.vutbr.cz)
 * @brief Declaration file of the Portal class. It derives from Model class and holds additional data
 * required for the implementation of portals.
 * @version 1.0
 * @date 2021-05-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include "Model.hpp"

#include <glm/glm.hpp>

/**
 * @brief This class represents portals as a non-euclidean objects.
 * 
 */
class Portal : public Model
{
public:
	Portal();

	/**
	 * @brief Loads a portal from a modified .obj file.
	 * 
	 * @param fileName Path to the .obj file.
	 */
	void loadFromFile(const std::string fileName);

	/**
	 * @brief Portal exit point.
	 * 
	 */
	glm::vec4 exit;

	/**
	 * @brief Portal geometric center.
	 * 
	 */
	glm::vec4 center;
};
