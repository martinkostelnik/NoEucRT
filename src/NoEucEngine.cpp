#include "NoEucEngine.hpp"

NoEucEngine::NoEucEngine() : window(sf::VideoMode(800, 600, 24), "Non-Euclidean Ray Tracer", sf::Style::None), renderer(), texture(), sprite(), scene()
{
	texture.create(800, 600);
	sprite.setTexture(texture);
}

int NoEucEngine::run()
{
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
			break;
		}
	}
}
