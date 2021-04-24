/**
 * @file RotationTunnel.hpp
 * @author Martin Kostelník (xkoste12@stud.fit.vutbr.cz)
 * @brief Declaration file of the RotationTunnel class. It derives from Model class and holds additional
 * required for the implementation of rotation tunnels.
 * @version 1.0
 * @date 2021-05-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include "Model.hpp"

class RotationTunnel : public Model
{
public:
	RotationTunnel();

	glm::vec4 direction;
	float maxRotation;
	float length;
};
