#pragma once

#include "Shader.hpp"

class PhongShader : public Shader
{
public:
	PhongShader();
	glm::vec3 getColor(const Ray& primaryRay, const Scene& scene, const Model& hitModel, const Triangle& hitTriangle, const float& distance) const;
};
