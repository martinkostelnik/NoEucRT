#include "Scene.hpp"

/************ DELETE THIS ************/
#include <iostream>
#include <glm/gtx/string_cast.hpp>
/*************************************/

Scene::Scene() :
	objects(),
	mainCamera()
{
}

Scene Scene::createBaseScene()
{
	Scene scene;

	Portal testingPortal;
	testingPortal.vertices = { { 300.0f, 100.0f, 400.0f, 1 }, {300.0f, -100.0f, 600.0f, 1 }, { 300.0f, -100.0f, 400.0f, 1 }, { 300.0f, 100.0f, 600.0f, 1 } };
	testingPortal.indices = { 0, 3, 1, 0, 1, 2 };
	testingPortal.center = (testingPortal.vertices[0] + testingPortal.vertices[1]) / 2.0f;
	testingPortal.exit = { 200.0f, 0.0f, -150.0f, 1.0f };
	scene.objects.push_back(std::make_shared<Portal>(testingPortal));
	
	/************************ Objects ************************/
	Model testingCube(Model::Type::Euclidean);
	testingCube.vertices = { {-100, -100, -100, 1}, {0, -100, -100, 1}, {0, 100, -100, 1}, {-100, 100, -100, 1},
							 {-100, -100, -200, 1}, {0, -100, -200, 1}, {0, 100, -200, 1}, {-100, 100, -200, 1} };
	testingCube.indices = { 0, 1, 2, 0, 2, 3, 0, 3, 4, 3, 7, 4, 6, 5, 4, 4, 7, 6, 1, 5, 2, 2, 5, 6, 0, 4, 1, 1, 4, 5, 2, 7, 3, 2, 6, 7 };
	testingCube.material.albedo = { 1.0f, 0.0f, 0.0f };
	testingCube.material.shininess = 50.0f;
	testingCube.material.kd = 1.0f;
	testingCube.material.ks = 0.04f;
	scene.objects.push_back(std::make_shared<Model>(testingCube));

	Model floor(Model::Type::Euclidean);
	floor.vertices = { {10000, -200, 10000, 1}, {10000, -200, -10000, 1}, {-10000, -200, -10000, 1}, {-10000, -200, 10000, 1} };
	floor.indices = { 0, 1, 2, 0, 2, 3 };
	floor.material.albedo = { 0.0f, 1.0f, 0.0f };
	floor.material.kd = 1.0f;
	floor.material.ks = 0.01f;
	floor.material.shininess = 25.0f;
	scene.objects.push_back(std::make_shared<Model>(floor));
	/*********************************************************/

	/************************* Lights ************************/
	Light l2({ 150, 100, -500, 1.0f }, 25000, { 1.0f, 1.0f, 1.0f }, Light::Type::Point);
	scene.lights.push_back(l2);

	Light sun({ 0, -1, 0, 0.0f }, 50, { 1.0f, 1.0f, 0.0f }, Light::Type::Distant);
	scene.lights.push_back(sun);
	/*********************************************************/

	return scene;
}

Scene Scene::createInfiniteTunnelScene()
{
	Scene scene;

	/************************ Objects ************************/
	Model floor(Model::Type::Euclidean);
	floor.vertices = { {400, -200, 350, 1}, {400, -200, -1150, 1}, {-400, -200, -1150, 1}, {-400, -200, 350, 1} };
	floor.indices = { 0, 1, 2, 0, 2, 3 };
	floor.material.albedo = { 0.0f, 1.0f, 0.0f };
	floor.material.kd = 1.0f;
	floor.material.ks = 0.0f;
	floor.material.shininess = 25.0f;
	scene.objects.push_back(std::make_shared<Model>(floor));

	Model leftWall(Model::Type::Euclidean);
	leftWall.vertices = { {-400, -200, 350, 1}, {-400, -200, -1150, 1}, {-400, 200, 350, 1}, {-400, 200, -1150, 1} };
	leftWall.indices = { 0, 1, 2, 1, 3, 2 };
	leftWall.material.albedo = { 0.0f, 1.0f, 0.0f };
	leftWall.material.kd = 1.0f;
	leftWall.material.ks = 0.0f;
	leftWall.material.shininess = 25.0f;
	scene.objects.push_back(std::make_shared<Model>(leftWall));

	Model topWall(Model::Type::Euclidean);
	topWall.vertices = { {-400, 200, 350, 1}, {400, 200, 350, 1}, {-400, 200, -1150, 1}, {400, 200, -1150, 1} };
	topWall.indices = { 0, 2, 1, 1, 2, 3 };
	topWall.material.albedo = { 0.0f, 1.0f, 0.0f };
	topWall.material.kd = 1.0f;
	topWall.material.ks = 0.01f;
	topWall.material.shininess = 25.0f;
	scene.objects.push_back(std::make_shared<Model>(topWall));

	Model rightWall(Model::Type::Euclidean);
	rightWall.vertices = { {400, -200, 350, 1}, {400, -200, -1150, 1}, {400, 200, 350, 1}, {400, 200, -1150, 1} };
	rightWall.indices = { 0, 2, 1, 1, 2, 3 };
	rightWall.material.albedo = { 0.0f, 1.0f, 0.0f };
	rightWall.material.kd = 1.0f;
	rightWall.material.ks = 0.0f;
	rightWall.material.shininess = 25.0f;
	scene.objects.push_back(std::make_shared<Model>(rightWall));
	/*********************************************************/

	/************************ Portals ************************/
	Portal frontPortal;
	frontPortal.vertices = { { -400.0f, -200.0f, -1150.0f, 1 }, {400.0f, -200.0f, -1150.0f, 1 }, { -400.0f, 200.0f, -1150.0f, 1 }, { 400.0f, 200.0f, -1150.0f, 1 } };
	frontPortal.indices = { 0, 1, 2, 1, 3, 2 };
	frontPortal.center = (frontPortal.vertices[0] + frontPortal.vertices[3]) / 2.0f;
	frontPortal.exit = { 0.0f, 0.0f, 300.0f, 1.0f };
	scene.objects.push_back(std::make_shared<Portal>(frontPortal));

	Portal backPortal;
	backPortal.vertices = { { -400.0f, -200.0f, 350.0f, 1 }, {400.0f, -200.0f, 350.0f, 1 }, { -400.0f, 200.0f, 350.0f, 1 }, { 400.0f, 200.0f, 350.0f, 1 } };
	backPortal.indices = { 0, 2, 1, 1, 2, 3};
	backPortal.center = (backPortal.vertices[1] + backPortal.vertices[2]) / 2.0f;
	backPortal.exit = { 0.0f, 0.0f, -1100.0f, 1.0f };
	scene.objects.push_back(std::make_shared<Portal>(backPortal));
	/*********************************************************/

	/************************* Lights ************************/
	Light l1({ -350, -150, 300, 0.0f }, 25000, { 1.0f, 1.0f, 1.0f }, Light::Type::Point);
	scene.lights.push_back(l1);

	Light l2({ 350, -150, 300, 0.0f }, 25000, { 1.0f, 1.0f, 1.0f }, Light::Type::Point);
	scene.lights.push_back(l2);
	
	Light l3({ -350, -150, -1100, 0.0f }, 25000, { 1.0f, 1.0f, 1.0f }, Light::Type::Point);
	scene.lights.push_back(l3);
	
	Light l4({ 350, -150, -1100, 0.0f }, 25000, { 1.0f, 1.0f, 1.0f }, Light::Type::Point);
	scene.lights.push_back(l4);
	/*********************************************************/
	return scene;
}

Scene Scene::createPortalScene()
{
	Scene scene;
	return scene;
}
