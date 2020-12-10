#include "Renderer.hpp"

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
	size_t n = (size_t)size.x * size.y * 4;

	for (size_t i = 0; i < n; i += 4)
	{
		// GENERATE RAY
		
		for (const auto& object : scene.objects)
		{
			// GET INTERSCTION
		}

		pixels[i] = std::abs(std::sin(i)) * 255;	// RED		
		pixels[i + 1] = std::abs(std::cos(i)) * 255;	// GREEN
		pixels[i + 2] = 0;	// BLUE
	}

	texture.update(pixels);
}
