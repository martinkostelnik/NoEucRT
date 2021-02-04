#include "NoEucEngine.hpp"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

NoEucEngine::NoEucEngine() : window(sf::VideoMode(800, 600, 24), "Non-Euclidean Ray Tracer", sf::Style::None), renderer(), texture(), sprite(), scene()
{
	texture.create(800, 600);
	sprite.setTexture(texture);
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

	auto start = std::chrono::high_resolution_clock::now();
	auto prev = std::chrono::high_resolution_clock::now();
	size_t frames = 0;

	while (window.isOpen())
	{
		// Process events
		handleEvents(prev);

		// Render image
		renderer.render(scene, texture);

		// Display image
		window.clear();
		window.draw(sprite);
		window.display();

		frames++;
	}

	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start);
	std::cout << "Avg fps: " << (double)frames / duration.count() << "\n";

	return 0;
}

void NoEucEngine::handleEvents(std::chrono::steady_clock::time_point& prev)
{
	auto now = std::chrono::high_resolution_clock::now();
	auto timeEllapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(now - prev);

	float d = timeEllapsed_ms.count() / 75.0;

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
				scene.mainCamera.toWorld = glm::translate(scene.mainCamera.toWorld, { 0, 0, -d * scene.mainCamera.speed });
			}
			if (event.key.code == sf::Keyboard::A)
			{
				scene.mainCamera.toWorld = glm::translate(scene.mainCamera.toWorld, { -d * scene.mainCamera.speed, 0, 0 });
			}
			if (event.key.code == sf::Keyboard::S)
			{
				scene.mainCamera.toWorld = glm::translate(scene.mainCamera.toWorld, { 0, 0, d * scene.mainCamera.speed });
			}
			if (event.key.code == sf::Keyboard::D)
			{
				scene.mainCamera.toWorld = glm::translate(scene.mainCamera.toWorld, { d * scene.mainCamera.speed, 0, 0 });
			}
			if (event.key.code == sf::Keyboard::Q)
			{
				scene.mainCamera.toWorld = glm::translate(scene.mainCamera.toWorld, { 0, -d * scene.mainCamera.speed, 0 });
			}
			if (event.key.code == sf::Keyboard::E)
			{
				scene.mainCamera.toWorld = glm::translate(scene.mainCamera.toWorld, { 0, d * scene.mainCamera.speed, 0 });
			}
			break;
		}
	}
	prev = now;
}
