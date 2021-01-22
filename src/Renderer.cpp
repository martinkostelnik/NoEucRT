#include "Renderer.hpp"
#include "Ray.hpp"

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
			d.x = tx;
			d.y = ty;
			ray.direction = d * scene.mainCamera.toWorld;
			ray.direction = glm::normalize(ray.direction);

			// Intersections
			float distance = 0.0;
			float minDistance = FLT_MAX;

			for (const auto& object : scene.objects)
			{
				for (const auto& triangle : object.triangles)
				{
					if (ray.intersectsTriangle(triangle, distance)) // distance is out parameter
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
