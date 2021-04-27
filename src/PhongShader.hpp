/**
 * @file PhongShader.hpp
 * @author Martin Kostelník (xkoste12@stud.fit.vutbr.cz)
 * @brief Declaration file of the PhongShader class, which implements Phong shading. It is derived from
 * Shader class.
 * @version 1.0
 * @date 2021-05-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include "Shader.hpp"

class PhongShader : public Shader
{
public:
	PhongShader();
	glm::vec3 getColor(const Ray& ray, const Scene& scene, const glm::vec4& hitPoint, const Model& hitModel, const Triangle& hitTriangle, const float u, const float v) const;
};
