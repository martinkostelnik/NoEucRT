#pragma once

#include <vector>

#include "Camera.hpp"

class Scene
{
public:
	Scene();
	std::vector<float> objects;

private:
	Camera mainCamera;
};
