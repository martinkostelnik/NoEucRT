#include "NoEucEngine.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include "LambertianShader.hpp"
#include "PhongShader.hpp"
#include "Portal.hpp"
#include "WarpedTunnel.hpp"

/************ DELETE THIS ************/
#include <iostream>
#include <glm/gtx/string_cast.hpp>
/*************************************/

// Rotacni tunel
// Zmensovaci tunel
// texturováni

NoEucEngine::NoEucEngine() :
	width(800),
	height(600),
	window(sf::VideoMode(width, height, 24), "Non-Euclidean Ray Tracer", sf::Style::None),
	scene(Scene::createBaseScene()),
	renderer(width, height, scene.mainCamera.fov),
	texture(),
	renderedImage(),
	movementClock(),
	fpsClock()
{
	texture.create(width, height);
	renderedImage.setTexture(texture);

	font.loadFromFile("arial.ttf");
	fpsText.setFont(font);
	fpsText.setCharacterSize(18);
	fpsText.setFillColor(sf::Color::Red);

	sceneName.setFont(font);
	sceneName.setCharacterSize(18);
	sceneName.setPosition(0.0f, 20.0f);
	sceneName.setFillColor(sf::Color::Red);
	sceneName.setString(scene.name);

	window.setMouseCursorVisible(false);
	sf::Mouse::setPosition(sf::Vector2i(width * 0.5, height * 0.5), window);

	shaders = { std::make_shared<LambertianShader>(LambertianShader()), std::make_shared<PhongShader>(PhongShader()) };
	shaderIndex = 0;
	activeShader = shaders[shaderIndex];
}

int NoEucEngine::run()
{
	// Model preprocessing
	for (auto& model : scene.objects)
	{
		// Transform every vertex to world space
		for (auto& vertex : model->vertices)
		{
			vertex = model->toWorld * vertex;
		}

		// Primitive assembly
		model->assembleTriangles();

		// Construst BVH on model
		model->buildAABB();
	}

	// Ray preprocessing, this function precomputes all ray directions in camera space.
	// Rays are then stored sequentially in a vector for simd support.
	renderer.precomputeRays();

	while (window.isOpen())
	{
		// Process events
		handleEvents();
		handleMovement();
		fpsText.setString("fps: " + std::to_string(1 / fpsClock.restart().asSeconds()));

		// Render image
		renderer.render(scene, *activeShader, texture);

		// Display image
		window.clear();
		window.draw(renderedImage);
		window.draw(fpsText);
		window.draw(sceneName);
		window.display();
	}

	return 0;
}

void NoEucEngine::handleEvents()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;

		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape)
			{
				window.close();
			}
			else if (event.key.code == sf::Keyboard::Q)
			{
				shaderIndex = shaderIndex == 0 ? 1 : 0;
				activeShader = shaders[shaderIndex];
			}
			else if (event.key.code == sf::Keyboard::E)
			{
				scene.mainCamera.reset();
			}
			break;

		default:
			break;
		}
	}
}

void NoEucEngine::handleMovement()
{
	sf::Time elapsedTime = movementClock.restart();

	// Rotation
	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

	// Get distance the mouse has moved in both directions
	float deltaX = mousePosition.x - width * 0.5;
	float deltaY = mousePosition.y - height * 0.5;

	// Save the previous rotation
	float tmpRotation = scene.mainCamera.Xrotation;
	scene.mainCamera.Xrotation -= deltaY;

	// Resolve maximum rotation around the X axis
	// Maximum rotation is set to 90 degrees
	if (scene.mainCamera.Xrotation > 90.0)
	{
		scene.mainCamera.Xrotation = 90.0;
		deltaY = -90.0 + tmpRotation;
	}
	else if (scene.mainCamera.Xrotation < -90.0)
	{
		scene.mainCamera.Xrotation = -90.0;
		deltaY = 90.0 + tmpRotation;
	}

	// Rotation around X axis
	scene.mainCamera.toWorld = glm::rotate(scene.mainCamera.toWorld, -glm::radians(deltaY), { 1, 0, 0 });

	// Rotation around Y axis
	scene.mainCamera.toWorld = glm::rotate(scene.mainCamera.toWorld, glm::radians(-scene.mainCamera.Xrotation), { 1, 0, 0 }); // Undo X axis rotation
	scene.mainCamera.toWorld = glm::rotate(scene.mainCamera.toWorld, -glm::radians(deltaX), { 0, 1, 0 });
	scene.mainCamera.toWorld = glm::rotate(scene.mainCamera.toWorld, glm::radians(scene.mainCamera.Xrotation), { 1, 0, 0 }); // Reapply X axis rotation

	// Reset mouse position to the middle of the window
	sf::Mouse::setPosition(sf::Vector2i(width * 0.5, height * 0.5), window);

	// Recalculate the lookAt vector
	scene.mainCamera.lookAt = scene.mainCamera.toWorld * glm::vec4(0.0f, 0.0f, -1.0f, 0.0f);

	// Movement
	float distance = elapsedTime.asSeconds() * scene.mainCamera.speed;
	glm::vec4 direction(0.0f);

	// Keyboard control
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		direction.z += -1.0f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		direction.x += -1.0f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		direction.z += 1.0f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		direction.x += 1.0f;
	}

	// Collision
	if (direction.x || direction.z)
	{
		scene.mainCamera.toWorld = glm::rotate(scene.mainCamera.toWorld, glm::radians(-scene.mainCamera.Xrotation), { 1, 0, 0 }); // Undo X axis rotation
		glm::vec4 worldDirection = scene.mainCamera.toWorld * direction;
		scene.mainCamera.toWorld = glm::rotate(scene.mainCamera.toWorld, glm::radians(scene.mainCamera.Xrotation), { 1, 0, 0 }); // Reapply X axis rotation

		Ray collisionRay(scene.mainCamera.position, glm::normalize(worldDirection));
		float hitDistance = 0.0f;

		// Test camera collision against each object in the scene
		[&] {
			for (const auto& object : scene.objects)
			{
				// Check if camera is inside warped tunnel
				if (object->type == Model::Type::WarpedTunnel && scene.mainCamera.isInsideAABB(object->boundingBox))
				{
					auto tunnel = static_cast<WarpedTunnel*>(object.get());

					scene.mainCamera.toWorld = glm::rotate(scene.mainCamera.toWorld, glm::radians(-scene.mainCamera.Xrotation), { 1, 0, 0 }); // Undo X axis rotation
					glm::vec4 localDirection = glm::inverse(scene.mainCamera.toWorld) * tunnel->direction;
					scene.mainCamera.toWorld = glm::rotate(scene.mainCamera.toWorld, glm::radians(scene.mainCamera.Xrotation), { 1, 0, 0 }); // Reapply X axis rotation
					
					float d = glm::dot(localDirection, direction);
					glm::vec4 warpedDirection = d > 0.0f ? glm::normalize(glm::mix(direction, localDirection, tunnel->intensity)) : glm::normalize(glm::mix(direction, -localDirection, tunnel->intensity));

					direction = glm::normalize(warpedDirection);

					float magnitude = glm::abs(glm::dot(direction, localDirection));
					distance = (distance * magnitude / tunnel->intensity) + (distance * (1 - magnitude));
					}

				if (collisionRay.intersectsAABB(object->boundingBox))
				{
					for (const auto& triangle : object->triangles)
					{
						if (collisionRay.intersectsTriangle(triangle, hitDistance))
						{
							if (hitDistance <= 5 || distance + 5 >= hitDistance) // We found the closest triangle the camera collides with
							{
								if (object->type == Model::Type::Euclidean)
								{
									distance = 0.0f;
								}
								else if (object->type == Model::Type::Portal)
								{
									glm::vec4 hitPoint = collisionRay.origin + collisionRay.direction * hitDistance;
									auto portal = static_cast<Portal*>(object.get());
									glm::vec4 outPoint(hitPoint + portal->exit - portal->center);

									distance -= hitDistance;
									scene.mainCamera.toWorld = glm::translate(glm::mat4(1.0f), { outPoint.x - hitPoint.x, 0, outPoint.z - hitPoint.z }) * scene.mainCamera.toWorld;
									scene.mainCamera.position = scene.mainCamera.toWorld * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
								}

								return;
							}
						}
					}
				}
			}
		}();
	}
	
	// Move camera
	scene.mainCamera.toWorld = glm::translate(scene.mainCamera.toWorld,
											 { direction.x * distance,
											   direction.z * glm::sin(glm::radians(scene.mainCamera.Xrotation)) * distance,
											   direction.z * glm::cos(glm::radians(scene.mainCamera.Xrotation)) * distance});

	// Recalculate camera position in world space
	scene.mainCamera.position = scene.mainCamera.toWorld * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	scene.mainCamera.position.y = 0.0f;
}
