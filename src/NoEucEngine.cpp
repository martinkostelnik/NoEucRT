/**
 * @file NoEucEngine.cpp
 * @author Martin Kostelník (xkoste12@stud.fit.vutbr.cz)
 * @brief Implementation file of the NoEucEngine class.
 * @version 1.0
 * @date 2021-05-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "NoEucEngine.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include "LambertianShader.hpp"
#include "PhongShader.hpp"
#include "Portal.hpp"
#include "WarpedTunnel.hpp"
#include "ShrinkTunnel.hpp"
#include "RotationTunnel.hpp"

NoEucEngine::NoEucEngine() :
	width(800),
	height(600),
	window(sf::VideoMode(width, height, 24), "Non-Euclidean Ray Tracer", sf::Style::None),
	scene(Scene::createBaseScene()),
	renderer(width, height, scene.mainCamera.fov),
	texture(),
	renderedImage(),
	fpsClock(),
	movementHandler()
{
	texture.create(width, height);
	renderedImage.setTexture(texture);

	font.loadFromFile("resources/opensans.ttf");
	fpsText.setFont(font);
	fpsText.setCharacterSize(18);
	fpsText.setFillColor(sf::Color::Red);

	sceneName.setFont(font);
	sceneName.setCharacterSize(18);
	sceneName.setPosition(0.0f, 20.0f);
	sceneName.setFillColor(sf::Color::Red);
	sceneName.setString(scene.name);

	window.setMouseCursorVisible(false);
	sf::Mouse::setPosition(sf::Vector2i(width * 0.5, height * 0.5), window);

	shaders.push_back(std::unique_ptr<Shader>(new LambertianShader()));
	shaders.push_back(std::unique_ptr<Shader>(new PhongShader()));
	shaderIndex = 0;
	activeShader = shaders[shaderIndex].get();
}

int NoEucEngine::run()
{
	// Preprocess scene
	scene.preProcessScene();

	// Ray preprocessing, this function precomputes all ray directions in camera space.
	// Rays are then stored sequentially in a vector for simd support.
	renderer.precomputeRays();

	while (window.isOpen())
	{
		// Process events
		handleEvents();

		// Handle movement
		movementHandler.handleMovement(window, scene, scene.mainCamera);
		
		// Update fps counter
		fpsText.setString("fps: " + std::to_string(1 / fpsClock.restart().asSeconds()));

		// Render image
		renderer.render(scene, *activeShader, texture);

		// Display image
		window.clear();
		window.draw(renderedImage);
		window.draw(fpsText);
		window.draw(sceneName);
		window.display();
	}

	return 0;
}

void NoEucEngine::handleEvents()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;

		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape)
			{
				window.close();
			}
			else if (event.key.code == sf::Keyboard::Q)
			{
				shaderIndex = shaderIndex == 0 ? 1 : 0;
				activeShader = shaders[shaderIndex].get();
			}
			else if (event.key.code == sf::Keyboard::E)
			{
				scene.mainCamera.reset();
			}
			else if (event.key.code == sf::Keyboard::Num1)
			{
				scene = Scene::createBaseScene();
				scene.preProcessScene();
				sceneName.setString(scene.name);
			}
			else if (event.key.code == sf::Keyboard::Num2)
			{
				scene = Scene::createPortalScene();
				scene.preProcessScene();
				sceneName.setString(scene.name);
			}
			else if (event.key.code == sf::Keyboard::Num3)
			{
				scene = Scene::createInfiniteTunnelScene();
				scene.preProcessScene();
				sceneName.setString(scene.name);
			}
			else if (event.key.code == sf::Keyboard::Num4)
			{
				scene = Scene::createShortTunnelScene();
				scene.preProcessScene();
				sceneName.setString(scene.name);
			}
			else if (event.key.code == sf::Keyboard::Num5)
			{
				scene = Scene::createLongTunnelScene();
				scene.preProcessScene();
				sceneName.setString(scene.name);
			}
			else if (event.key.code == sf::Keyboard::Num6)
			{
				scene = Scene::createShrinkScene();
				scene.preProcessScene();
				sceneName.setString(scene.name);
			}
			else if (event.key.code == sf::Keyboard::Num7)
			{
				scene = Scene::createRotatingTunnelScene();
				scene.preProcessScene();
				sceneName.setString(scene.name);
			}
			else if (event.key.code == sf::Keyboard::Num8)
			{
				scene = Scene::createRotatingTunnelScene2();
				scene.preProcessScene();
				sceneName.setString(scene.name);
			}
			break;

		default:
			break;
		}
	}
}
