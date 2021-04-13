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