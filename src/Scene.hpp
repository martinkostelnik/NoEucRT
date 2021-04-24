#pragma once

#include <vector>
#include <memory>

#include "Camera.hpp"
#include "Model.hpp"
#include "Light.hpp"
#include "Skybox.hpp"

class Scene
{
public:
	Scene();

	std::string name;
	std::vector<std::unique_ptr<Model>> objects;
	std::vector<Light> lights;
	Camera mainCamera;
	Skybox skybox;
	float floorLevel;

	static Scene createBaseScene();
	static Scene createPortalScene();
	static Scene createInfiniteTunnelScene();
	static Scene createShortTunnelScene();
	static Scene createLongTunnelScene();
	static Scene createShrinkScene();
};
