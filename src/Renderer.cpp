#include "Renderer.hpp"
#include "Ray.hpp"
#include <iostream>

Renderer::Renderer()
{
	constexpr size_t len = 800 * 600 * 4;

	pixels = new sf::Uint8[len] { 0 };

	for (int i = 3; i < len; i += 4)
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
	float scale = tan(scene.mainCamera.fov * 0.00872665);

	glm::vec4 d = { 0, 0, -1, 0 };
	float distance = 0.0;
	float minDistance = FLT_MAX;

	for (size_t y = 0; y < size.y; y++)
	{
		for (size_t x = 0; x < size.x; x++)
		{
			Ray primaryRay({ (2 * (x + 0.5) / (float)size.x - 1) * scale * aspectRatio, (1 - 2 * (y + 0.5) / (float)size.y) * scale, -1, 0 });

			// Transform ray origin using camera world transformation matrix
			//ray.origin = scene.mainCamera.toWorld * ray.origin;
			primaryRay.origin = {
				primaryRay.origin.x * scene.mainCamera.toWorld[0].x + primaryRay.origin.y * scene.mainCamera.toWorld[1].x + primaryRay.origin.z * scene.mainCamera.toWorld[2].x + primaryRay.origin.w * scene.mainCamera.toWorld[3].x,
				primaryRay.origin.x * scene.mainCamera.toWorld[0].y + primaryRay.origin.y * scene.mainCamera.toWorld[1].y + primaryRay.origin.z * scene.mainCamera.toWorld[2].y + primaryRay.origin.w * scene.mainCamera.toWorld[3].y,
				primaryRay.origin.x * scene.mainCamera.toWorld[0].z + primaryRay.origin.y * scene.mainCamera.toWorld[1].z + primaryRay.origin.z * scene.mainCamera.toWorld[2].z + primaryRay.origin.w * scene.mainCamera.toWorld[3].z,
				primaryRay.origin.x * scene.mainCamera.toWorld[0].w + primaryRay.origin.y * scene.mainCamera.toWorld[1].w + primaryRay.origin.z * scene.mainCamera.toWorld[2].w + primaryRay.origin.w * scene.mainCamera.toWorld[3].w
			};

			// Calculate ray direction and transform it using camera world transformation matrix
			//ray.direction = scene.mainCamera.toWorld * d;
			primaryRay.direction = {
				primaryRay.direction.x * scene.mainCamera.toWorld[0].x + primaryRay.direction.y * scene.mainCamera.toWorld[1].x + primaryRay.direction.z * scene.mainCamera.toWorld[2].x + primaryRay.direction.w * scene.mainCamera.toWorld[3].x,
				primaryRay.direction.x * scene.mainCamera.toWorld[0].y + primaryRay.direction.y * scene.mainCamera.toWorld[1].y + primaryRay.direction.z * scene.mainCamera.toWorld[2].y + primaryRay.direction.w * scene.mainCamera.toWorld[3].y,
				primaryRay.direction.x * scene.mainCamera.toWorld[0].z + primaryRay.direction.y * scene.mainCamera.toWorld[1].z + primaryRay.direction.z * scene.mainCamera.toWorld[2].z + primaryRay.direction.w * scene.mainCamera.toWorld[3].z,
				primaryRay.direction.x * scene.mainCamera.toWorld[0].w + primaryRay.direction.y * scene.mainCamera.toWorld[1].w + primaryRay.direction.z * scene.mainCamera.toWorld[2].w + primaryRay.direction.w * scene.mainCamera.toWorld[3].w
			};

			// Do we need to normalize?
			//ray.direction = glm::normalize(ray.direction);

			// Intersections
			distance = 0.0;
			minDistance = FLT_MAX;

			for (const auto& object : scene.objects)
			{
				for (const auto& triangle : object.triangles)
				{
					if (primaryRay.intersectsTriangle(triangle, distance)) // distance is out parameter
					{
						if (distance < minDistance)
						{
							minDistance = distance;

							// Shading
							pixels[position] = 255;	// RED
							pixels[position + 1] = 0;	// GREEN
							pixels[position + 2] = 0;	// BLUE
						}
					}
				}
			}

			position += 4;
		}
	}
	texture.update(pixels);
}
