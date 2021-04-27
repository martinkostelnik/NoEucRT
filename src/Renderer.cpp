/**
 * @file Renderer.cpp
 * @author Martin Kostelník (xkoste12@stud.fit.vutbr.cz)
 * @brief Implementation file of the Renderer class.
 * @version 1.0
 * @date 2021-05-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "Renderer.hpp"

#include "Ray.hpp"
#include "Portal.hpp"
#include "WarpedTunnel.hpp"

Renderer::Renderer(const size_t width, const size_t height, const float& fov) : 
	width(width),
	height(height),
	aspectRatio(width / (float)height),
	fov(fov)
{
	const size_t len = width * height * 4;

	pixels = std::unique_ptr<sf::Uint8[]>(new sf::Uint8[len] { 0 });

	for (int i = 3; i < len; i += 4)
	{
		pixels[i] = 255;
	}
}

void Renderer::precomputeRays()
{
	precomputedRays.reserve(width * height);
	primaryRays.reserve(width * height);
	
	// scale = tan(alpha/2 * pi/180)
	float scale = tan(fov * 0.00872665f);

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			precomputedRays.emplace_back(Ray({ (2 * (x + 0.5) / (float)width - 1) * scale * aspectRatio, (1 - 2 * (y + 0.5) / (float)height) * scale, -1, 0 }));
			primaryRays.emplace_back(Ray());
		}
	}
}

Renderer::castRayData Renderer::castRay(const Ray& ray, const Scene& scene, const bool warped, const glm::vec4& prevDirection) const
{
	castRayData data = { false, 0, nullptr, {0.0f, 0.0f, 0.0f, 1.0f}, ray, 0.0f, 0.0f };
	float distance = 0.0f;
	float minDistance = std::numeric_limits<float>::infinity();

	#pragma omp parallel for private(distance)
	for (int i = 0; i < scene.objects.size(); i++)
	{
		if (ray.intersectsAABB(scene.objects[i]->boundingBox))
		{
			for (const auto& triangle : scene.objects[i]->triangles)
			{
				if (ray.intersectsTriangle(triangle, distance, &data.u, &data.v)) // distance is out parameter
				{
					data.hit = true;

					if (distance < minDistance)
					{
						minDistance = distance;
						data.hitObjectIndex = i;
						data.hitTriangle = &triangle;
					}
				}
			}
		}
	}

	if (data.hit)
	{
		data.hitPoint = ray.origin + ray.direction * minDistance;

		const float bias = 1e-4f;

		// Portal handling
		if (scene.objects[data.hitObjectIndex]->type == Model::Type::Portal)
		{
			// Erase hit data
			data.hit = false;

			auto portal = static_cast<Portal*>(scene.objects[data.hitObjectIndex].get());

			glm::vec4 outPoint(data.hitPoint + portal->exit - portal->center);

			Ray teleportedRay(outPoint, ray.direction);
			data.ray = teleportedRay;

			data = castRay(teleportedRay, scene);
		}
		else if (scene.objects[data.hitObjectIndex]->type == Model::Type::WarpedTunnel)
		{
			if (!warped) // Ray entering warping tunnel
			{
				data.hit = false;

				auto tunnel = static_cast<WarpedTunnel*>(scene.objects[data.hitObjectIndex].get());

				float d = glm::dot(tunnel->warpDirection, ray.direction);
				glm::vec4 warpedDirection(0.0f);

				if (tunnel->compressed)
				{
					warpedDirection = glm::normalize(ray.direction + d * tunnel->warpDirection * tunnel->intensity);
				}
				else
				{
					warpedDirection = glm::normalize(ray.direction - d * tunnel->warpDirection * tunnel->intensity);
				}

				Ray warpedRay(data.hitPoint + ray.direction * bias, warpedDirection);
				data = castRay(warpedRay, scene, true, ray.direction);
			}
			else // Ray leaving warping tunnel
			{
				data.hit = false;

				Ray leavingRay(data.hitPoint + ray.direction * bias, prevDirection);
				data = castRay(leavingRay, scene);
			}
		}
		else if (scene.objects[data.hitObjectIndex]->type == Model::Type::ShrinkTunnel || scene.objects[data.hitObjectIndex]->type == Model::Type::RotationTunnel)
		{
			data.hit = false;
			Ray r(data.hitPoint + ray.direction * bias, ray.direction);

			data = castRay(r, scene);
		}
	}

	return data;
}

void Renderer::render(const Scene& scene, const Shader& shader, sf::Texture& texture)
{
	const sf::Vector2u size = texture.getSize();

	// Transform all rays to world space
	#pragma omp parallel for
	for (int i = 0; i < primaryRays.size(); i++)
	{
		primaryRays[i].origin = scene.mainCamera.toWorld * precomputedRays[i].origin;
		primaryRays[i].direction = scene.mainCamera.toWorld * precomputedRays[i].direction;
	}

	// Check if we are in warped tunnel
	// If yes, we have to recompute ray directions
	bool warped = false;
	#pragma omp parallel for
	for (int i = 0; i < scene.objects.size(); i++)
	{
		if (scene.objects[i]->type == Model::Type::WarpedTunnel)
		{
			if (scene.mainCamera.isInsideAABB(scene.objects[i]->boundingBox))
			{
				warped = true;
				auto tunnel = static_cast<WarpedTunnel*>(scene.objects[i].get());

				#pragma omp parallel for
				for (int j = 0; j < primaryRays.size(); j++)
				{
					float d = glm::dot(tunnel->warpDirection, primaryRays[j].direction);

					if (tunnel->compressed)
					{
						primaryRays[j].direction = glm::normalize(primaryRays[j].direction + d * tunnel->warpDirection * tunnel->intensity);
					}
					else
					{
						primaryRays[j].direction = glm::normalize(primaryRays[j].direction - d * tunnel->warpDirection * tunnel->intensity);
					}
				}

				break;
			}
		}
	}

	// Render an image
	#pragma omp parallel for
	for (int y = 0; y < size.y; y++)
	{
		#pragma omp parallel for
		for (int x = 0; x < size.x; x++)
		{
			const size_t position = size_t(y) * size.x + x;

			// Cast ray into the scene
			castRayData data = castRay(primaryRays[position], scene, warped, scene.mainCamera.toWorld * precomputedRays[position].direction);

			glm::vec3 color(0.0f);

			if (data.hit) // We hit something, invoke shader and set color
			{
				color = shader.getColor(data.ray, scene, data.hitPoint, *scene.objects[data.hitObjectIndex], *data.hitTriangle, data.u, data.v);
			}
			else // We hit nothing
			{
				color = scene.skybox.getColor(glm::normalize(data.ray.direction));

			}

			pixels[position * 4] = color.r; // RED
			pixels[position * 4 + 1] = color.g; // GREEN
			pixels[position * 4 + 2] = color.b; // Blue
		}
	}

	texture.update(pixels.get());
}
