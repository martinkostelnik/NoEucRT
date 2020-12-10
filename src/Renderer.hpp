#pragma once

#include <SFML/Graphics.hpp>

#include "Scene.hpp"

class Renderer
{
public:
	Renderer();
	~Renderer();
	void render(const Scene& s, sf::Texture& t);

private:
	sf::Uint8* pixels;
};
