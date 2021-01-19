#pragma once

#include <vector>

#include "Camera.hpp"
#include "Model.hpp"

class Scene
{
public:
	Scene();

	std::vector<Model> objects;
	Camera mainCamera;
};
