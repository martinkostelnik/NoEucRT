#pragma once

#include <SFML/Graphics.hpp>

class Renderer
{
public:
	Renderer();
	~Renderer();
	void render(sf::Texture& t);

private:
	sf::Uint8* pixels;
};
