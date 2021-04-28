/**
 * @file Scene.hpp
 * @author Martin Kostelník (xkoste12@stud.fit.vutbr.cz)
 * @brief Declaration file of the Scene class. This class holds all the objects, lights and 
 * other neccessary things required for rendering. It also contains static methods to create sample scenes.
 * Class is also responsible for pre-processing related to optimalizations.
 * @version 1.0
 * @date 2021-05-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

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
	static Scene createRotatingTunnelScene();
	static Scene createRotatingTunnelScene2();

	void preProcessScene();
};
