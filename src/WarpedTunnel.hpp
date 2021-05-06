/**
 * @file WarpedTunnel.hpp
 * @author Martin Kostelník (xkoste12@stud.fit.vutbr.cz)
 * @brief Declaration file of the WarpedTunnel class. It derives from Model class and holds additional data
 * required for the implementation of warped tunnels.
 * @version 1.0
 * @date 2021-05-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include "Model.hpp"

class WarpedTunnel : public Model
{
public:
	WarpedTunnel();

	void loadFromFile(const std::string fileName);

	glm::vec4 warpDirection;
	float intensity;
	bool compressed;
};
