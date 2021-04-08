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
