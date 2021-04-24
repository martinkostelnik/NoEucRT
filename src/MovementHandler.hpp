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

	void handleCollision(const Scene& scene, Camera& camera, glm::vec4& direction, float& distance);
	void handleRotation(const sf::RenderWindow& window, const Scene& scene, Camera& camera) const;
	void handleTranslation(const Scene& scene, Camera& camera);
};