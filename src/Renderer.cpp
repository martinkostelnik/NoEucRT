#include "Renderer.hpp"
#include "Ray.hpp"

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

void Renderer::render(const Scene& scene, sf::Texture& texture)
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
			bool hit = false;
			float distance = 0.0;
			float minDistance = FLT_MAX;

			for (const auto& object : scene.objects)
			{
				if (primaryRays[position].intersectsAABB(object.boundingBox))
				{
					for (const auto& triangle : object.triangles)
					{
						if (primaryRays[position].intersectsTriangle(triangle, distance)) // distance is out parameter
						{
							hit = true;

							if (distance < minDistance)
							{
								minDistance = distance;

								// Shading
								pixels[position * 4] = 255;	// RED
								pixels[position * 4 + 1] = 0; // GREEN
								pixels[position * 4 + 2] = 0; // BLUE
							}
						}
					}
				}
			}

			if (!hit) // we hit nothing -- set black
			{
				pixels[position * 4] = 0; // RED
				pixels[position * 4 + 1] = 0; // GREEN
				pixels[position * 4 + 2] = 0; // BLUE
			}
		}
	}
	texture.update(pixels);
}
