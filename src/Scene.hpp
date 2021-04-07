#pragma once

#include <vector>
#include <memory>

#include "Camera.hpp"
#include "Model.hpp"
#include "Light.hpp"

class Scene
{
public:
	Scene();

	std::vector<std::unique_ptr<Model>> objects;
	std::vector<Light> lights;
	Camera mainCamera;


	static Scene createBaseScene();
};
