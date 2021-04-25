/**
 * @file MovementHandler.cpp
 * @author Martin Kostelník (xkoste12@stud.fit.vutbr.cz)
 * @brief Implementation file of the MovementHandler class.
 * @version 1.0
 * @date 2021-05-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "MovementHandler.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Portal.hpp"
#include "WarpedTunnel.hpp"
#include "ShrinkTunnel.hpp"
#include "RotationTunnel.hpp"

/************ DELETE THIS ************/
#include <iostream>
#include <glm/gtx/string_cast.hpp>
/*************************************/

MovementHandler::MovementHandler() :
	movementClock(),
	inside(false)
{
}

void MovementHandler::handleMovement(const sf::RenderWindow& window, const Scene& scene, Camera& camera)
{
	handleRotation(window, scene, camera);
	handleTranslation(scene, camera);
}

void MovementHandler::handleRotation(const sf::RenderWindow& window, const Scene& scene, Camera& camera) const
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
	const size_t width = window.getSize().x;
	const size_t height = window.getSize().y;

	// Get distance the mouse has moved in both directions
	float deltaX = mousePosition.x - width * 0.5;
	float deltaY = mousePosition.y - height * 0.5;

	// Save the previous rotation
	float tmpRotation = camera.Xrotation;
	camera.Xrotation -= deltaY;

	// Resolve maximum rotation around the X axis
	// Maximum X rotation is set to 90 degrees
	if (camera.Xrotation > 90.0)
	{
		camera.Xrotation = 90.0;
		deltaY = -90.0 + tmpRotation;
	}
	else if (camera.Xrotation < -90.0)
	{
		camera.Xrotation = -90.0;
		deltaY = 90.0 + tmpRotation;
	}

	// Rotation around X axis
	camera.toWorld = glm::rotate(camera.toWorld, -glm::radians(deltaY), { 1, 0, 0 });

	// Rotation around Y axis
	camera.toWorld = glm::rotate(camera.toWorld, glm::radians(-camera.Xrotation), { 1, 0, 0 }); // Undo X axis rotation
	camera.toWorld = glm::rotate(camera.toWorld, -glm::radians(deltaX), { 0, 1, 0 });
	camera.toWorld = glm::rotate(camera.toWorld, glm::radians(camera.Xrotation), { 1, 0, 0 }); // Reapply X axis rotation

	// Reset mouse position to the middle of the window
	sf::Mouse::setPosition(sf::Vector2i(width * 0.5, height * 0.5), window);

	// Recalculate the lookAt vector
	camera.lookAt = camera.toWorld * glm::vec4(0.0f, 0.0f, -1.0f, 0.0f);
}

void MovementHandler::handleTranslation(const Scene& scene, Camera& camera)
{
	sf::Time elapsedTime = movementClock.restart();
	float distance = elapsedTime.asSeconds() * camera.speed;
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

	// Collision handling. Collision can only happen when moving
	if (direction.x || direction.z)
	{
		handleCollision(scene, camera, direction, distance);
	}

	// Move camera
	camera.toWorld = glm::translate(camera.toWorld,
		{ direction.x * distance,
		  direction.z * glm::sin(glm::radians(camera.Xrotation)) * distance,
		  direction.z * glm::cos(glm::radians(camera.Xrotation)) * distance });

	// Recalculate camera position in world space
	camera.position = camera.toWorld * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
}

void MovementHandler::handleCollision(const Scene& scene, Camera& camera, glm::vec4& direction, float& distance)
{
	// First we calculate movement direction in world space
	camera.toWorld = glm::rotate(camera.toWorld, glm::radians(-camera.Xrotation), { 1, 0, 0 }); // Undo X axis rotation
	glm::vec4 worldDirection = glm::normalize(camera.toWorld * direction);
	camera.toWorld = glm::rotate(camera.toWorld, glm::radians(camera.Xrotation), { 1, 0, 0 }); // Reapply X axis rotation

	// Create collision ray
	Ray collisionRay(camera.position, worldDirection);
	float hitDistance = 0.0f;

	// Test camera collision against each object in the scene
	for (const auto& object : scene.objects)
	{
		// Check if camera is inside an object
		// We might need to change direction or distance based on the non-euclidean things
		if (camera.isInsideAABB(object->boundingBox))
		{
			inside = true;

			if (object->type == Model::Type::WarpedTunnel) // We are inside warping tunnel
			{
				auto tunnel = static_cast<WarpedTunnel*>(object.get());

				// Undo X axis rotation
				camera.toWorld = glm::rotate(camera.toWorld, glm::radians(-camera.Xrotation), { 1, 0, 0 });

				// Get tunnel movement direction in camera space
				glm::vec4 localDirection = glm::inverse(camera.toWorld) * tunnel->warpDirection;

				// Calculate alignment of movement direction with tunnel direction
				float alignment = glm::dot(localDirection, direction);
				float magnitude = glm::abs(alignment);

				glm::vec4 warpedDirection = direction + alignment * localDirection * tunnel->intensity;

				if (tunnel->compressed)
				{
					warpedDirection = direction + alignment * localDirection * tunnel->intensity;
					distance = (distance * magnitude * tunnel->intensity) + (distance * (1 - magnitude));
				}
				else
				{
					warpedDirection = direction - alignment * localDirection * tunnel->intensity;
					distance = (distance * magnitude * (1 - tunnel->intensity)) + (distance * (1 - magnitude));
				}

				direction = glm::normalize(warpedDirection);
				collisionRay.direction = glm::normalize(camera.toWorld * direction);

				// Reapply X axis rotation
				camera.toWorld = glm::rotate(camera.toWorld, glm::radians(camera.Xrotation), { 1, 0, 0 });
			}
			else if (object->type == Model::Type::ShrinkTunnel) // We are inside shrinking tunnel
			{
				auto tunnel = static_cast<ShrinkTunnel*>(object.get());
				glm::vec4 localDirection = glm::inverse(camera.toWorld) * tunnel->direction;

				float distanceToShrink = distance * glm::dot(localDirection, direction);

				float shrinkFraction = distanceToShrink / tunnel->length;

				float yDistance = (camera.position.y - scene.floorLevel) * shrinkFraction * tunnel->finalSize;

				// Test for collision, this has to been done here before actual collision checks
				if (camera.position.y - yDistance < tunnel->ceiling - 5 && camera.position.y - yDistance > scene.floorLevel + 5)
				{
					// Change speed appropriately to size
					camera.speed *= 1 - yDistance / (camera.position.y - scene.floorLevel);

					camera.toWorld = glm::translate(glm::mat4(1.0f), { 0.0f, -yDistance, 0.0f }) * camera.toWorld;
					camera.position = camera.toWorld * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
				}
				else {
					distance = 0.0f;
				}
			}
			else if (object->type == Model::Type::RotationTunnel) // We are inside rotation tunnel
			{
				auto tunnel = static_cast<RotationTunnel*>(object.get());
				glm::vec4 localDirection = glm::inverse(camera.toWorld) * tunnel->direction;

				float distanceToRotate = distance * glm::dot(localDirection, direction);

				float rotateFraction = distanceToRotate / tunnel->length;

				float rotation = glm::radians(tunnel->maxRotation * rotateFraction);

				camera.toWorld = glm::rotate(camera.toWorld, rotation, { 0, 0, 1 });
			}
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
							auto portal = static_cast<Portal*>(object.get());

							glm::vec4 hitPoint = collisionRay.origin + collisionRay.direction * hitDistance;
							glm::vec4 outPoint(hitPoint + portal->exit - portal->center);

							distance -= hitDistance;

							camera.toWorld = glm::translate(glm::mat4(1.0f), { outPoint.x - hitPoint.x, outPoint.y - hitPoint.y, outPoint.z - hitPoint.z }) * camera.toWorld;
							camera.position = camera.toWorld * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
						}
						else if (object->type == Model::Type::WarpedTunnel || object->type == Model::Type::RotationTunnel)
						{
							if (!inside) // Entering warped tunnel
							{
								distance = hitDistance + 1;
							}
						}
						else if (object->type == Model::Type::ShrinkTunnel)
						{
							auto tunnel = static_cast<ShrinkTunnel*>(object.get());
							float distanceInTunnel = inside ? hitDistance : distance - hitDistance;

							float a = distanceInTunnel * glm::dot(glm::normalize(glm::vec2(worldDirection.x, worldDirection.z)), glm::normalize(glm::vec2(tunnel->direction.x, tunnel->direction.z)));
							float f = a / tunnel->length;

							float yDistance = (camera.position.y - scene.floorLevel) * f * tunnel->finalSize;

							camera.toWorld = glm::translate(glm::mat4(1.0f), { 0.0f, -yDistance, 0.0f }) * camera.toWorld;
							camera.position = camera.toWorld * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
						}

						return;
					}
				}
			}
		}
	}
}
