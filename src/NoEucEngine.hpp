#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "Renderer.hpp"
#include "Scene.hpp"
#include "Shader.hpp"
#include "MovementHandler.hpp"

class NoEucEngine
{
public:
	NoEucEngine();
	int run();

private:
	const size_t width;
	const size_t height;

	sf::Texture texture;
	sf::Sprite renderedImage;

	Scene scene;
	sf::RenderWindow window;
	Renderer renderer;

	MovementHandler movementHandler;

	sf::Clock fpsClock;

	sf::Font font;
	sf::Text fpsText;
	sf::Text sceneName;

	void handleEvents();

	std::vector<std::unique_ptr<Shader>> shaders;
	size_t shaderIndex;
	Shader* activeShader;
};
