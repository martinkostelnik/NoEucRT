#pragma once

#include <SFML/Graphics.hpp>

#include "Scene.hpp"

class Renderer
{
public:
	Renderer();
	~Renderer();
	void render(const Scene& scene, sf::Texture& texture);

private:
	sf::Uint8* pixels;
};
