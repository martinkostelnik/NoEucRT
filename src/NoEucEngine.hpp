#pragma once

#include <SFML/Graphics.hpp>

#include "Renderer.hpp"
#include "Scene.hpp"

class NoEucEngine
{
public:
	NoEucEngine();
	int run();

private:
	sf::Texture texture;
	sf::Sprite renderedImage;

	Scene scene;
	sf::RenderWindow window;
	Renderer renderer;

	sf::Clock movementClock;

	sf::Font fpsFont;
	sf::Text fpsText;

	void handleEvents();
	void handleMovement();
};
