#include "Renderer.hpp"
#include <iostream>


Renderer::Renderer()
{
	pixels = new sf::Uint8[800 * 600 * 4];
	*pixels = { 255 };
}

Renderer::~Renderer()
{
	delete[] pixels;
}

void Renderer::render(const Scene& scene, sf::Texture& texture)
{
	sf::Vector2u size = texture.getSize();
	size_t position = 0;

	for (size_t y = 0; y < size.y; y++)
	{
		for (size_t x = 0; x < size.x; x++)
		{
			// GENERATE RAY

			for (const auto& object : scene.objects)
			{
				// GET INTERSCTION
			}

			position = (y * size.x + x) * 4;
			pixels[position] = std::abs(std::sin(position * 0.001)) * 255;	// RED
			pixels[position + 1] = 255 - std::abs(std::sin(position * 0.001)) * 255;	// GREEN
			pixels[position + 2] = 0;	// BLUE
		}
	}

	texture.update(pixels);
}
