#pragma once

#include "Shader.hpp"

class LambertianShader : public Shader
{
public:
	LambertianShader();
	glm::vec3 getColor(const Ray& ray, const Scene& scene, const glm::vec4& hitPoint, const Model& hitModel, const Triangle& hitTriangle) const;
};
