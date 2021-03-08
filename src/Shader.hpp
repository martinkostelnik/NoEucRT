#pragma once
#include <glm/glm.hpp>
#include "Ray.hpp"
#include "Scene.hpp"
#include "Model.hpp"

class Shader
{
public:
	Shader();
	virtual glm::vec3 getColor(const Ray& primaryRay, const Scene& scene, const Model& hitModel, const Triangle& hitTriangle, const float& distance) const = 0;
};
