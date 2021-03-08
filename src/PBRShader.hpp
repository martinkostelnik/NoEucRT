#pragma once

#include "Shader.hpp"

class PBRShader : public Shader
{
public:
	PBRShader();
	glm::vec3 getColor(const Ray& primaryRay, const Scene& scene, const Model& hitModel, const Triangle& hitTriangle, const float& distance) const;
};
