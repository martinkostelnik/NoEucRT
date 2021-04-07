#include "Renderer.hpp"

#include "Ray.hpp"
#include "Portal.hpp"

#include <iostream>

Renderer::Renderer(const size_t width, const size_t height, const float& fov) : 
	width(width),
	height(height),
	aspectRatio(width / (float)height),
	fov(fov)
{
	const size_t len = width * height * 4;

	pixels = new sf::Uint8[len] { 0 };

	for (int i = 3; i < len; i += 4)
		pixels[i] = 255;
}

Renderer::~Renderer()
{
	delete[] pixels;
}

void Renderer::precomputeRays()
{
	precomputedRays.reserve(width * height);
	primaryRays.reserve(width * height);
	
	// scale = tan(alpha/2 * pi/180)
	float scale = tan(fov * 0.00872665);

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			precomputedRays.emplace_back(Ray({ (2 * (x + 0.5) / (float)width - 1) * scale * aspectRatio, (1 - 2 * (y + 0.5) / (float)height) * scale, -1, 0 }));
			primaryRays.emplace_back(Ray());
		}
	}
}

Renderer::castRayData Renderer::castRay(const Ray& ray, const Scene& scene) const
{
	castRayData data = { false, 0, nullptr, std::numeric_limits<float>::infinity() };
	float distance = 0.0f;

	for (size_t i = 0; i < scene.objects.size(); i++)
	{
		if (ray.intersectsAABB(scene.objects[i]->boundingBox))
		{
			for (const auto& triangle : scene.objects[i]->triangles)
			{
				if (ray.intersectsTriangle(triangle, distance)) // distance is out parameter
				{
					data.hit = true;

					if (distance < data.hitDistance)
					{
						data.hitDistance = distance;
						data.hitObjectIndex = i;
						data.hitTriangle = &triangle;
					}
				}
			}
		}
	}

	// Portal handling
	if (scene.objects[data.hitObjectIndex]->type == Model::Type::Portal)
	{
		glm::vec4 hitPoint = ray.origin + glm::normalize(ray.direction) * data.hitDistance;
		auto portal = std::static_pointer_cast<const Portal>(scene.objects[data.hitObjectIndex]);

		glm::vec4 outPoint(hitPoint + portal->exit - portal->center);

		Ray teleportedRay(outPoint, ray.direction);
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

	// Render an image
	#pragma omp parallel for
	for (int y = 0; y < size.y; y++)
	{
		#pragma omp parallel for
		for (int x = 0; x < size.x; x++)
		{
			size_t position = ((y * size.x) + x);

			castRayData data = castRay(primaryRays[position], scene);

			if (data.hit) // We hit something, invoke shader and set color
			{
				glm::vec3 color = shader.getColor(primaryRays[position], scene, *scene.objects[data.hitObjectIndex], *data.hitTriangle, data.hitDistance);
				pixels[position * 4] = color.x;	// RED
				pixels[position * 4 + 1] = color.y; // GREEN
				pixels[position * 4 + 2] = color.z; // BLUE
			}
			else // We hit nothing
			{
				pixels[position * 4] = 0; // RED
				pixels[position * 4 + 1] = 191; // GREEN
				pixels[position * 4 + 2] = 255; // BLUE
			}
		}
	}

	texture.update(pixels);
}
