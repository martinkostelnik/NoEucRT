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

class Shader
{
public:
	Shader();
	virtual glm::vec3 getColor(const Ray& ray, const Scene& scene, const glm::vec4& hitPoint, const Model& hitModel, const Triangle& hitTriangle) const = 0;
};
