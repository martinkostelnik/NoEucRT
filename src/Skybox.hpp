/**
 * @file Skzbox.hpp
 * @author Martin Kostelník (xkoste12@stud.fit.vutbr.cz)
 * @brief Declaration file of the Skybox class. It holds data related to skybox, which gives
 * the scene more immersion and depth.
 * @version 1.0
 * @date 2021-05-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>

class Skybox
{
public:
	Skybox(const std::string fileName);
	sf::Image cubeMap;
	std::vector<glm::vec2> mapping;

	sf::Color getColor(const glm::vec4& rayDirection) const;

private:
	size_t faceSize;
};