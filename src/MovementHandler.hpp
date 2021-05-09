/**
 * @file MovementHandler.hpp
 * @author Martin Kostelník (xkoste12@stud.fit.vutbr.cz)
 * @brief Declaration file of the MovementHandler class. The engine uses a single instance of this class
 * to handle movement of the camera in the scene and through non-euclidean objects.
 * @version 1.0
 * @date 2021-05-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include <SFML/Graphics.hpp>
#include "Scene.hpp"
#include "Ray.hpp"

class MovementHandler
{
public:
	MovementHandler();

	void handleMovement(const sf::RenderWindow& window, const Scene& scene, Camera& camera);

private:
	sf::Clock movementClock;
	bool inside;
	float shrinkEntryHeight;
	float shrinkEntrySpeed;

	void handleCollision(const Scene& scene, Camera& camera, glm::vec4& direction, float& distance);
	void handleRotation(const sf::RenderWindow& window, const Scene& scene, Camera& camera) const;
	void handleTranslation(const Scene& scene, Camera& camera);
};
