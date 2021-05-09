/**
 * @file LambertianShader.hpp
 * @author Martin Kostelník (xkoste12@stud.fit.vutbr.cz)
 * @brief Declaration file of the LambertianShader class. This class implements Lambertian shading.
 * @version 1.0
 * @date 2021-05-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include "Shader.hpp"

class LambertianShader : public Shader
{
public:
	LambertianShader();
	glm::vec3 getColor(const Ray& ray, const Scene& scene, const glm::vec4& hitPoint, const Model& hitModel, const Triangle& hitTriangle, const float u, const float v) const;
};
