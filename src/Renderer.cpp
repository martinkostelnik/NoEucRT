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

	// scale = tan(alpha/2 * pi/180)
	float scale = tan(scene.mainCamera.fov * 0.00872665);
	float distance = 0.0;
	float minDistance = FLT_MAX;

	#pragma omp parallel for private(distance, minDistance)
	for (int y = 0; y < size.y; y++)
	{
		#pragma omp parallel for
		for (int x = 0; x < size.x; x++)
		{
			size_t position = ((y * size.x) + x) * 4;
			bool hit = false;

			Ray primaryRay({ (2 * (x + 0.5) / (float)size.x - 1) * scale * aspectRatio, (1 - 2 * (y + 0.5) / (float)size.y) * scale, -1, 0 });

			// Transform ray origin using camera world transformation matrix
			// Calculate ray direction and transform it using camera world transformation matrix
			#pragma omp simd
			for (int i = 0; i < 4; i++)
			{
				primaryRay.origin[i] = primaryRay.origin.x * scene.mainCamera.toWorld[0][i] + primaryRay.origin.y * scene.mainCamera.toWorld[1][i] + primaryRay.origin.z * scene.mainCamera.toWorld[2][i] + primaryRay.origin.w * scene.mainCamera.toWorld[3][i];
				primaryRay.direction[i] = primaryRay.direction.x * scene.mainCamera.toWorld[0][i] + primaryRay.direction.y * scene.mainCamera.toWorld[1][i] + primaryRay.direction.z * scene.mainCamera.toWorld[2][i] + primaryRay.direction.w * scene.mainCamera.toWorld[3][i];
			}

			distance = 0.0;
			minDistance = FLT_MAX;

			for (const auto& object : scene.objects)
			{
				for (const auto& triangle : object.triangles)
				{
					if (primaryRay.intersectsTriangle(triangle, distance)) // distance is out parameter
					{
						hit = true;

						if (distance < minDistance)
						{
							minDistance = distance;

							// Shading
							pixels[position] = 255;	// RED
							pixels[position + 1] = 0; // GREEN
							pixels[position + 2] = 0; // BLUE
						}
					}
				}
			}

			if (!hit) // we hit nothing -- set black
			{
				pixels[position] = 0; // RED
				pixels[position + 1] = 0; // GREEN
				pixels[position + 2] = 0; // BLUE
			}
		}
	}
	texture.update(pixels);
}
