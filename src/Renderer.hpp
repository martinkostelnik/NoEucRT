#pragma once

#include <SFML/Graphics.hpp>

#include "Scene.hpp"
#include "Ray.hpp"

class Renderer
{
public:
	Renderer(const size_t width, const size_t height, const float& fov);
	~Renderer();
	void render(const Scene& scene, sf::Texture& texture);
	void precomputeRays();

private:
	const size_t width;
	const size_t height;
	const float aspectRatio;
	const float& fov;

	sf::Uint8* pixels;
	std::vector<Ray> precomputedRays;
	std::vector<Ray> primaryRays;
};
