#pragma once

#include <SFML/Graphics.hpp>

#include "Scene.hpp"
#include "Ray.hpp"
#include "Shader.hpp"

class Renderer
{
public:
	Renderer(const size_t width, const size_t height, const float& fov);
	~Renderer();
	void render(const Scene& scene, const Shader& shader, sf::Texture& texture);
	void precomputeRays();

private:
	struct castRayData
	{
		bool hit;
		size_t hitObjectIndex;
		const Triangle* hitTriangle;
		glm::vec4 hitPoint;
		Ray ray;
	};

	castRayData castRay(const Ray& ray, const Scene& scene) const;

	const size_t width;
	const size_t height;
	const float aspectRatio;
	const float& fov;

	sf::Uint8* pixels;
	std::vector<Ray> precomputedRays;
	std::vector<Ray> primaryRays;
};
