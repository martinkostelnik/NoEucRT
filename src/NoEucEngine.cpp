#include "NoEucEngine.hpp"
#include <chrono>
#include <iostream>

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
	size_t frames = 0;

	while (window.isOpen())
	{
		// Process events
		handleEvents();

		// Update

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
			break;
		}
	}
}
