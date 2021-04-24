/**
 * @file ShrinkTunnel.hpp
 * @author Martin Kostelník (xkoste12@stud.fit.vutbr.cz)
 * @brief Declaration file of the ShrinkTunnel class. It derives from Model class and holds additional data
 * required for the implementation of tunnels, which shrink the player character.
 * @version 1.0
 * @date 2021-05-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include "Model.hpp"

class ShrinkTunnel : public Model
{
public:
	ShrinkTunnel();

	glm::vec4 direction;
	float finalSize;
	float length;
	float ceiling;
};
