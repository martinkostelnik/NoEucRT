/**
 * @file Renderer.hpp
 * @author Martin Kostelník (xkoste12@stud.fit.vutbr.cz)
 * @brief Declaration file of the Renderer class. Instance of this class is used to produce an image
 * using the ray-tracing method. It also defined ray behaviour in non-euclidean spaces.
 * @version 1.0
 * @date 2021-05-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include <SFML/Graphics.hpp>

#include "Scene.hpp"
#include "Ray.hpp"
#include "Shader.hpp"

class Renderer
{
public:
	Renderer(const size_t width, const size_t height, const float& fov);
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
		float u;
		float v;
	};

	castRayData castRay(const Ray& ray, const Scene& scene, const bool warped = false, const glm::vec4& prevDirection = { 0.0f, 0.0f, 0.0f, 0.0f }) const;

	const size_t width;
	const size_t height;
	const float aspectRatio;
	const float& fov;

	std::unique_ptr<sf::Uint8[]> pixels;
	std::vector<Ray> precomputedRays;
	std::vector<Ray> primaryRays;
};
