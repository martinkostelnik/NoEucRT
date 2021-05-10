/**
 * @file Skybox.hpp
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

/**
 * @brief This class represents a cubemap skybox around the scene.
 * 
 */
class Skybox
{
public:
	Skybox(const std::string fileName);

	/**
	 * @brief Texture of the skybox.
	 * 
	 */
	sf::Image cubeMap;

	/**
	 * @brief Cube mapping.
	 * 
	 */
	std::vector<glm::vec2> mapping;

	/**
	 * @brief This method computes a point on a skybox texture from ray direction.
	 * 
	 * @param rayDirection Ray direction
	 * @return glm::vec3 Returns color from a point on the skybox texture.
	 */
	glm::vec3 getColor(const glm::vec4& rayDirection) const;

private:
	/**
	 * @brief Face size of cube map
	 * 
	 */
	size_t faceSize;
};
