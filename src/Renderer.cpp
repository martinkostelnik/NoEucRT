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


void Renderer::precomputeRays(const float fov)
{
	precomputedRays.reserve(800 * 600);
	primaryRays.reserve(800 * 600);
	
	// scale = tan(alpha/2 * pi/180)
	float scale = tan(fov * 0.00872665);

	for (int y = 0; y < 600; y++)
	{
		for (int x = 0; x < 800; x++)
		{
			precomputedRays.emplace_back(Ray({ (2 * (x + 0.5) / (float)800 - 1) * scale * aspectRatio, (1 - 2 * (y + 0.5) / (float)600) * scale, -1, 0 }));
			primaryRays.emplace_back(Ray());
		}
	}
}

void Renderer::render(const Scene& scene, sf::Texture& texture)
{
	const sf::Vector2u size = texture.getSize();

	// Transform all rays to world space
	for (int y = 0; y < size.y; y++)
	{
		for (int x = 0; x < size.x; x++)
		{
			size_t position = y * size.x + x;

			for (int i = 0; i < 4; i++)
			{
				primaryRays[position].origin[i] = precomputedRays[position].origin.x * scene.mainCamera.toWorld[0][i] + precomputedRays[position].origin.y * scene.mainCamera.toWorld[1][i] + precomputedRays[position].origin.z * scene.mainCamera.toWorld[2][i] + precomputedRays[position].origin.w * scene.mainCamera.toWorld[3][i];
				primaryRays[position].direction[i] = precomputedRays[position].direction.x * scene.mainCamera.toWorld[0][i] + precomputedRays[position].direction.y * scene.mainCamera.toWorld[1][i] + precomputedRays[position].direction.z * scene.mainCamera.toWorld[2][i] + precomputedRays[position].direction.w * scene.mainCamera.toWorld[3][i];
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
			size_t position = ((y * size.x) + x) * 4;
			bool hit = false;
			float distance = 0.0;
			float minDistance = FLT_MAX;

			for (const auto& object : scene.objects)
			{
				for (const auto& triangle : object.triangles)
				{
					if (primaryRays[position / 4].intersectsTriangle(triangle, distance)) // distance is out parameter
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
