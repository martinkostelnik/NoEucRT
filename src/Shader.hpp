/**
 * @file Shader.hpp
 * @author Martin Kostelník (xkoste12@stud.fit.vutbr.cz)
 * @brief Declaration file of the Shader class, which is a pure virtual class for shading.
 * @version 1.0
 * @date 2021-05-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include <glm/glm.hpp>

#include "Ray.hpp"
#include "Scene.hpp"
#include "Model.hpp"

/**
 * @brief Abstact class which desribes a shader.
 * 
 */
class Shader
{
public:
	Shader();
	
	/**
	 * @brief Get the color of a point on an object.
	 * 
	 * @param ray The incoming ray.
	 * @param scene Scene
	 * @param hitPoint Examined point on an object.
	 * @param hitModel Examined object.
	 * @param hitTriangle Examined triangle.
	 * @param u Texture coordinate.
	 * @param v Texture coordinate.
	 * @return glm::vec3 Returns the color of a point on an object.
	 */
	virtual glm::vec3 getColor(const Ray& ray, const Scene& scene, const glm::vec4& hitPoint, const Model& hitModel, const Triangle& hitTriangle, const float u, const float v) const = 0;
};
