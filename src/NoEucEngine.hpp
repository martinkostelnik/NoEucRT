#pragma once

#include <SFML/Graphics.hpp>
#include <chrono>

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

	void handleEvents(std::chrono::steady_clock::time_point& prev);
};
