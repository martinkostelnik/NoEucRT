#pragma once

#include <SFML/Graphics.hpp>

#include "Scene.hpp"
#include "Ray.hpp"

class Renderer
{
public:
	Renderer();
	~Renderer();
	void render(const Scene& scene, sf::Texture& texture);
	void precomputeRays(const float fov);

private:
	sf::Uint8* pixels;
	float aspectRatio;
	std::vector<Ray> precomputedRays;
	std::vector<Ray> primaryRays;
};
