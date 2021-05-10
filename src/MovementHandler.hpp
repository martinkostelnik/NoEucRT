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

/**
 * @brief An object of this class is used to handle movement inside a scene with non-euclidean spaces.
 * 
 */
class MovementHandler
{
public:
	MovementHandler();

	/**
	 * @brief This method does the actual movement handling.
	 * 
	 * @param window Window of the application used to compute mouse movement.
	 * @param scene Scene that the camera moves in.
	 * @param camera This camera is manipulated with.
	 */
	void handleMovement(const sf::RenderWindow& window, const Scene& scene, Camera& camera);

private:
	/**
	 * @brief Clock used to measure movement.
	 * 
	 */
	sf::Clock movementClock;

	/**
	 * @brief Indicates if we are inside an object.
	 * 
	 */
	bool inside;

	/**
	 * @brief Used to determine movement in shrinking tunnel.
	 * 
	 */
	float shrinkEntryHeight;

		/**
	 * @brief Used to determine movement in shrinking tunnel.
	 * 
	 */
	float shrinkEntrySpeed;

	/**
	 * @brief Collision handling system.
	 * 
	 * @param scene 
	 * @param camera 
	 * @param direction Movement direction.
	 * @param distance Movement distance.
	 */
	void handleCollision(const Scene& scene, Camera& camera, glm::vec4& direction, float& distance);

	/**
	 * @brief Rotation handling system.
	 * 
	 * @param window 
	 * @param scene 
	 * @param camera 
	 */
	void handleRotation(const sf::RenderWindow& window, const Scene& scene, Camera& camera) const;

	/**
	 * @brief Translation handling system.
	 * 
	 * @param scene 
	 * @param camera 
	 */
	void handleTranslation(const Scene& scene, Camera& camera);
};
