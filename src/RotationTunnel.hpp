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

/**
 * @brief This class represents rotation tunnels as a non-euclidean objects.
 * 
 */
class RotationTunnel : public Model
{
public:
	RotationTunnel();

	/**
	 * @brief Loads a rotation tunnel from a modified .obj file.
	 * 
	 * @param fileName Path to the .obj file.
	 */
	void loadFromFile(const std::string fileName);

	glm::vec4 direction;

	/**
	 * @brief Rotation performed when the whole tunnel is traversed.
	 * 
	 */
	float maxRotation;

	/**
	 * @brief Axes around which the camera is rotated.
	 * 
	 */
	glm::vec3 axes;

	/**
	 * @brief Tunnel length.
	 * 
	 */
	float length;
};
