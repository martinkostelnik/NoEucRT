#pragma once

#include <vector>

#include "Camera.hpp"
#include "Model.hpp"
#include "Light.hpp"

class Scene
{
public:
	Scene();

	std::vector<Model> objects;
	std::vector<Light> lights;
	Camera mainCamera;
};
