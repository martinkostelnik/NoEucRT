#include "NoEucEngine.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include "LambertianShader.hpp"
#include "PhongShader.hpp"

/************ DELETE THIS ************/
#include <iostream>
#include <glm/gtx/string_cast.hpp>
/*************************************/

NoEucEngine::NoEucEngine() :
	width(800),
	height(600),
	window(sf::VideoMode(width, height, 24), "Non-Euclidean Ray Tracer", sf::Style::None),
	scene(),
	renderer(width, height, scene.mainCamera.fov),
	texture(),
	renderedImage(),
	movementClock()
{
	texture.create(width, height);
	renderedImage.setTexture(texture);

	fpsFont.loadFromFile("arial.ttf");
	fpsText.setFont(fpsFont);
	fpsText.setCharacterSize(18);
	fpsText.setFillColor(sf::Color::Red);

	window.setMouseCursorVisible(false);
	sf::Mouse::setPosition(sf::Vector2i(width * 0.5, height * 0.5), window);

	shaders = { new LambertianShader(), new PhongShader() };
	shaderIndex = 0;
	activeShader = shaders[shaderIndex];
}

int NoEucEngine::run()
{
	// Model preprocessing
	for (auto& model : scene.objects)
	{
		// Transform every vertex to world space
		for (auto& vertex : model.vertices)
		{
			vertex = model.toWorld * vertex;
		}

		// Primitive assembly
		model.assembleTriangles();

		// Construst BVH on model
		model.constructBVH();
	}

	// Ray preprocessing, this function precomputes all ray directions in camera space.
	// Rays are then stored sequentially in a vector for simd support.
	renderer.precomputeRays();

	sf::Clock fpsClock;

	while (window.isOpen())
	{
		// Process events
		handleEvents();
		handleMovement();
		fpsText.setString(std::to_string(1 / fpsClock.restart().asSeconds()));

		// Render image
		renderer.render(scene, *activeShader, texture);

		// Display image
		window.clear();
		window.draw(renderedImage);
		window.draw(fpsText);
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
	glm::mat4 tmpMatrix = scene.mainCamera.toWorld;
	const float distance = elapsedTime.asSeconds() * scene.mainCamera.speed;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		scene.mainCamera.toWorld = glm::translate(scene.mainCamera.toWorld,
			{ 0,
			  -glm::sin(glm::radians(scene.mainCamera.Xrotation)) * distance,
			  -glm::cos(glm::radians(scene.mainCamera.Xrotation)) * distance });
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		scene.mainCamera.toWorld = glm::translate(scene.mainCamera.toWorld, { -distance, 0, 0 });
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		scene.mainCamera.toWorld = glm::translate(scene.mainCamera.toWorld,
			{ 0,
			  glm::sin(glm::radians(scene.mainCamera.Xrotation)) * distance,
			  glm::cos(glm::radians(scene.mainCamera.Xrotation)) * distance });
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		scene.mainCamera.toWorld = glm::translate(scene.mainCamera.toWorld, { distance, 0, 0 });
	}

	// Recalculate camera position in world space
	scene.mainCamera.position = scene.mainCamera.toWorld * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

	for (const auto& model : scene.objects)
	{
		if (scene.mainCamera.AABBCollision(model.boundingBox))
		{
			scene.mainCamera.toWorld = tmpMatrix;
			break;
		}
	}
}
