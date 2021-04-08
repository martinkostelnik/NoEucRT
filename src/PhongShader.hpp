#pragma once

#include "Shader.hpp"

class PhongShader : public Shader
{
public:
	PhongShader();
	glm::vec3 getColor(const Ray& ray, const Scene& scene, const glm::vec4& hitPoint, const Model& hitModel, const Triangle& hitTriangle) const;
};
