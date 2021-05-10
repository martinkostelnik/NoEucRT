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

/**
 * @brief This class represents warped tunnels as a non-euclidean objects.
 * 
 */
class WarpedTunnel : public Model
{
public:
	WarpedTunnel();

	
	/**
	 * @brief Loads a warped tunnel from a modified .obj file.
	 * 
	 * @param fileName Path to the .obj file.
	 */
	void loadFromFile(const std::string fileName);

	/**
	 * @brief Direction which the ray is warped towards.
	 * 
	 */
	glm::vec4 warpDirection;

	/**
	 * @brief Warping intensity.
	 * 
	 */
	float intensity;

	/**
	 * @brief Indicates wheter the tunnel is compressed or prolonged.
	 * 
	 */
	bool compressed;
};
