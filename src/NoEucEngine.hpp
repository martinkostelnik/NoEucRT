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
	sf::Sprite sprite;

	Scene scene;
	sf::RenderWindow window;
	Renderer renderer;

	void handleEvents();
};
