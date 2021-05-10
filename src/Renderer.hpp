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

/**
 * @brief This class is responsible for image rendering using ray-tracing.
 * 
 */
class Renderer
{
public:
	Renderer(const size_t width, const size_t height, const float& fov);

	/**
	 * @brief Renders an image of a scene.
	 * 
	 * @param scene Scene to be rendered
	 * @param shader Used shader.
	 * @param texture Out parameter, this texture contains the rendered image.
	 */
	void render(const Scene& scene, const Shader& shader, sf::Texture& texture);

	/**
	 * @brief Precomputes all rays in camera space.
	 * 
	 */
	void precomputeRays();

private:

	/**
	 * @brief Contains data about ray traversal.
	 * 
	 */
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

	/**
	 * @brief Casts a ray into the scene.
	 * 
	 * @param ray
	 * @param scene 
	 * @param warped Indicates whether the ray was already warped by a non-euclidean object.
	 * @param prevDirection Previous ray direction.
	 * @return castRayData Returns traversal data.
	 */
	castRayData castRay(const Ray& ray, const Scene& scene, const bool warped = false, const glm::vec4& prevDirection = { 0.0f, 0.0f, 0.0f, 0.0f }) const;

	const size_t width;
	const size_t height;
	const float aspectRatio;
	const float& fov;

	/**
	 * @brief Rendered image inside main memory, this is later copied into the texture.
	 * 
	 */
	std::unique_ptr<sf::Uint8[]> pixels;

	/**
	 * @brief Precomputed rays in the camera space.
	 * 
	 */
	std::vector<Ray> precomputedRays;

	/**
	 * @brief Primary rays in world space.
	 * 
	 */
	std::vector<Ray> primaryRays;
};
