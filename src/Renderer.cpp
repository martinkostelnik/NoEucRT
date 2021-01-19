#include "Renderer.hpp"
#include <iostream>

#include "Ray.hpp"

Renderer::Renderer()
{
	pixels = new sf::Uint8[800 * 600 * 4];

	for (int i = 0; i < 800 * 600 * 4; i++)
		pixels[i] = 0;

	for (int i = 3; i < 800 * 600 * 4; i += 4)
		pixels[i] = 255;

	aspectRatio = 800 / (float)600;
}

Renderer::~Renderer()
{
	delete[] pixels;
}

void Renderer::render(const Scene& scene, sf::Texture& texture)
{
	sf::Vector2u size = texture.getSize();
	size_t position = 0;

	// scale = tan(alpha/2 * pi/180)
	float scale = tan(scene.mainCamera.fov * 0.5 * 3.14159265358979 / 180);

	for (size_t y = 0; y < size.y; y++)
	{
		for (size_t x = 0; x < size.x; x++)
		{
			// Transform x, y from raster space to camera space
			float tx = (2 * (x + 0.5) / (float)size.x - 1) * scale * aspectRatio;
			float ty = (1 - 2 * (y + 0.5) / (float)size.y) * scale;

			Ray ray;

			// Transform ray origin using camera world transformation matrix
			ray.origin = ray.origin * scene.mainCamera.toWorld;

			// Calculate ray direction and transform it using camera world transformation matrix
			ray.direction = glm::vec4(tx, ty, -1, 0) * scene.mainCamera.toWorld;
			ray.direction = glm::normalize(ray.direction);

			// Intersections
			float distance = 0.0;
			float minDistance = FLT_MAX;
			size_t closestTriangleIndex = 0;

			for (const auto& object : scene.objects)
			{
				for (size_t i = 0; i < object.indices.size(); i += 3)
				{
					if (ray.intersectsTriangle(Triangle(object.vertices[object.indices[i]], object.vertices[object.indices[i + 1]], object.vertices[object.indices[i + 2]]), distance)) // distance is out parameter
					{
						if (distance < minDistance)
						{
							minDistance = distance;
							closestTriangleIndex = i;
						}

						// Shading
						pixels[position] = 255;	// RED
						pixels[position + 1] = 0;	// GREEN
						pixels[position + 2] = 0;	// BLUE
					}
				}
			}

			position += 4;
		}
	}

	texture.update(pixels);
}
