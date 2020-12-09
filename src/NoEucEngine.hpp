#pragma once

#include <SFML/Graphics.hpp>

#include "Renderer.hpp"

class NoEucEngine
{
public:
	sf::RenderWindow window;
	Renderer renderer;

	NoEucEngine();
	int run();

private:
	sf::Texture t;
	sf::Sprite s;

	void handleEvents();
};
