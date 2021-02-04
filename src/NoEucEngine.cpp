#include "NoEucEngine.hpp"
#include <iostream>
#include <string>
#include <glm/gtc/matrix_transform.hpp>

NoEucEngine::NoEucEngine() : window(sf::VideoMode(800, 600, 24), "Non-Euclidean Ray Tracer", sf::Style::None), renderer(), texture(), renderedImage(), scene(), movementClock()
{
	texture.create(800, 600);
	renderedImage.setTexture(texture);

	fpsFont.loadFromFile("arial.ttf");
	fpsText.setFont(fpsFont);
	fpsText.setCharacterSize(18);
	fpsText.setFillColor(sf::Color::Red);
}

int NoEucEngine::run()
{
	// Transform objects
	for (auto& model : scene.objects)
	{
		for (auto& vertex : model.vertices)
		{
			vertex = model.toWorld * vertex;
		}
	}

	// Primitive assembly
	for (auto& model : scene.objects)
	{
		model.assembleTriangles();
	}

	sf::Clock fpsClock;
	sf::Clock movementClock;

	while (window.isOpen())
	{
		// Process events
		handleEvents();
		fpsText.setString(std::to_string(1 / fpsClock.restart().asSeconds()));

		// Render image
		renderer.render(scene, texture);

		// Display image
		window.clear();
		window.draw(renderedImage);
		window.draw(fpsText);
		window.display();
	}

	return 0;
}

void NoEucEngine::handleEvents()
{
	sf::Time elapsedTime = movementClock.restart();

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
			if (event.key.code == sf::Keyboard::W)
			{
				scene.mainCamera.toWorld = glm::translate(scene.mainCamera.toWorld, { 0, 0, -elapsedTime.asSeconds() * scene.mainCamera.speed });
			}
			if (event.key.code == sf::Keyboard::A)
			{
				scene.mainCamera.toWorld = glm::translate(scene.mainCamera.toWorld, { -elapsedTime.asSeconds() * scene.mainCamera.speed, 0, 0 });
			}
			if (event.key.code == sf::Keyboard::S)
			{
				scene.mainCamera.toWorld = glm::translate(scene.mainCamera.toWorld, { 0, 0, elapsedTime.asSeconds() * scene.mainCamera.speed });
			}
			if (event.key.code == sf::Keyboard::D)
			{
				scene.mainCamera.toWorld = glm::translate(scene.mainCamera.toWorld, { elapsedTime.asSeconds() * scene.mainCamera.speed, 0, 0 });
			}
			if (event.key.code == sf::Keyboard::Q)
			{
				scene.mainCamera.toWorld = glm::translate(scene.mainCamera.toWorld, { 0, -elapsedTime.asSeconds() * scene.mainCamera.speed, 0 });
			}
			if (event.key.code == sf::Keyboard::E)
			{
				scene.mainCamera.toWorld = glm::translate(scene.mainCamera.toWorld, { 0, elapsedTime.asSeconds() * scene.mainCamera.speed, 0 });
			}
			break;
		}
	}
}
