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

/**
 * @brief This class represents shrinking tunnels as a non-euclidean objects.
 * 
 */
class ShrinkTunnel : public Model
{
public:
	ShrinkTunnel();

	/**
	 * @brief Loads a shrinking tunnel from a modified .obj file.
	 * 
	 * @param fileName Path to the .obj file.
	 */
	void loadFromFile(const std::string fileName);

	glm::vec4 direction;

	/**
	 * @brief Fraction representing final size after tunnel traversal.
	 * 
	 */
	float finalSize;

	/**
	 * @brief Tunnel length.
	 * 
	 */
	float length;

	/**
	 * @brief Y coordinate of tunnel ceiling
	 * 
	 */
	float ceiling;
};
