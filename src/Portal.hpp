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

class Portal : public Model
{
public:
	Portal();

	void loadFromFile(const std::string fileName);

	glm::vec4 exit;
	glm::vec4 center;
};
