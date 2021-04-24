/**
 * @file NoEucEngine.hpp
 * @author Martin Kostelník (xkoste12@stud.fit.vutbr.cz)
 * @brief Declaration file of the NoEucEngine class. This is the class that combines all the
 * other classes and suits as an interface between them. It also handles UI, which is very simple,
 * consisting only of two lines of texts. Lastly it handles system events.
 * @version 1.0
 * @date 2021-05-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

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
