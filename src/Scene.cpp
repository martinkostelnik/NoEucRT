/**
 * @file Scene.cpp
 * @author Martin Kostelník (xkoste12@stud.fit.vutbr.cz)
 * @brief Implementation file of the Scene class.
 * @version 1.0
 * @date 2021-05-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "Scene.hpp"

#include "Portal.hpp"
#include "WarpedTunnel.hpp"
#include "ShrinkTunnel.hpp"
#include "RotationTunnel.hpp"

#include <iostream>

Scene::Scene() :
	objects(),
	mainCamera(),
	skybox("resources/skybox.png"),
	floorLevel(0.0f)
{
}

Scene Scene::createBaseScene()
{
	Scene scene;
	scene.name = "Basic scene";
	scene.floorLevel = -200;

	/************************ Objects ************************/
	std::unique_ptr<Model> testingCube { new Model(Model::Type::Euclidean) };
	testingCube->loadFromFile("resources/testingCube.obj");
	testingCube->material.loadFromFile("resources/phongMaterial.mtl");
	scene.objects.push_back(std::move(testingCube));

	std::unique_ptr<Model> floor { new Model(Model::Type::Euclidean) };
	floor->loadFromFile("resources/floor.obj");
	floor->material.loadFromFile("resources/diffuseMaterial.mtl");
	floor->texture.loadFromFile("resources/texture.png");
	scene.objects.push_back(std::move(floor));
	/*********************************************************/

	/************************* Lights ************************/
	Light l2({ 650, 70,-700, 1.0f }, 25000, { 1.0f, 1.0f, 1.0f }, Light::Type::Point);
	scene.lights.push_back(l2);

	Light l1({ 650, 70, 100, 1.0f }, 25000, { 1.0f, 1.0f, 1.0f }, Light::Type::Point);
	scene.lights.push_back(l1);

	Light sun({ 0, -1, 0, 0.0f }, 50, { 1.0f, 1.0f, 0.0f }, Light::Type::Distant);
	scene.lights.push_back(sun);
	/*********************************************************/

	return scene;
}

Scene Scene::createPortalScene()
{
	Scene scene;

	scene.name = "Simple portal";

	/************************ Objects ************************/
	Model floor1(Model::Type::Euclidean);
	floor1.vertices = { {-400, -100, 100, 1}, {-400, -100, -600, 1}, {400, -100, 100, 1}, {400, -100, -600, 1} };
	floor1.indices = { 0, 2, 1, 2, 3, 1 };
	floor1.material.albedo = { 0.0f, 1.0f, 0.0f };
	floor1.material.kd = 1.0f;
	floor1.material.ks = 0.001f;
	floor1.material.shininess = 15.0f;
	scene.objects.push_back(std::make_unique<Model>(floor1));
	scene.floorLevel = -100;

	Model leftWall(Model::Type::Euclidean);
	leftWall.vertices = { {-300, -100, -400, 1}, {-300, -100, -500, 1}, {-300, 150, -400, 1}, {-300, 150, -500, 1} };
	leftWall.indices = { 0, 3, 1, 0, 2, 3 };
	leftWall.material.albedo = { 0.0f, 1.0f, 0.0f };
	leftWall.material.kd = 1.0f;
	leftWall.material.ks = 0.01f;
	leftWall.material.shininess = 25.0f;
	scene.objects.push_back(std::make_unique<Model>(leftWall));

	Model frontWall1(Model::Type::Euclidean);
	frontWall1.vertices = { {-300, -100, -400, 1}, {-300, 50, -400, 1}, {-50, -100, -400, 1}, {-50, 50, -400, 1} };
	frontWall1.indices = { 0, 2, 1, 2, 3, 1 };
	frontWall1.material.albedo = { 0.0f, 1.0f, 0.0f };
	frontWall1.material.kd = 1.0f;
	frontWall1.material.ks = 0.01f;
	frontWall1.material.shininess = 25.0f;
	scene.objects.push_back(std::make_unique<Model>(frontWall1));

	Model frontWall2(Model::Type::Euclidean);
	frontWall2.vertices = { {50, -100, -400, 1}, {50, 50, -400, 1}, {300, -100, -400, 1}, {300, 50, -400, 1} };
	frontWall2.indices = { 0, 2, 1, 2, 3, 1 };
	frontWall2.material.albedo = { 0.0f, 1.0f, 0.0f };
	frontWall2.material.kd = 1.0f;
	frontWall2.material.ks = 0.01f;
	frontWall2.material.shininess = 25.0f;
	scene.objects.push_back(std::make_unique<Model>(frontWall2));

	Model rightWall(Model::Type::Euclidean);
	rightWall.vertices = { {300, -100, -400, 1}, {300, -100, -500, 1}, {300, 150, -400, 1}, {300, 150, -500, 1} };
	rightWall.indices = { 0, 1, 2, 1, 3, 2 };
	rightWall.material.albedo = { 0.0f, 1.0f, 0.0f };
	rightWall.material.kd = 1.0f;
	rightWall.material.ks = 0.01f;
	rightWall.material.shininess = 25.0f;
	scene.objects.push_back(std::make_unique<Model>(rightWall));

	Model frontWall3(Model::Type::Euclidean);
	frontWall3.vertices = { {-300, 50, -400, 1}, {-300, 150, -400, 1}, {300, 50, -400, 1}, {300, 150, -400, 1} };
	frontWall3.indices = { 0, 2, 1, 2, 3, 1 };
	frontWall3.material.albedo = { 0.0f, 1.0f, 0.0f };
	frontWall3.material.kd = 1.0f;
	frontWall3.material.ks = 0.01f;
	frontWall3.material.shininess = 25.0f;
	scene.objects.push_back(std::make_unique<Model>(frontWall3));

	Model topWall(Model::Type::Euclidean);
	topWall.vertices = { {-300, 150, -400, 1}, {-300, 150, -500, 1}, {300, 150, -400, 1}, {300, 150, -500, 1} };
	topWall.indices = { 0, 2, 1, 2, 3, 1 };
	topWall.material.albedo = { 0.0f, 1.0f, 0.0f };
	topWall.material.kd = 1.0f;
	topWall.material.ks = 0.01f;
	topWall.material.shininess = 25.0f;
	scene.objects.push_back(std::make_unique<Model>(topWall));

	Model backWall(Model::Type::Euclidean);
	backWall.vertices = { {-300, -100, -500, 1}, {-300, 150, -500, 1}, {300, -100, -500, 1}, {300, 150, -500, 1} };
	backWall.indices = { 2, 0, 3, 0, 1, 3 };
	backWall.material.albedo = { 0.0f, 1.0f, 0.0f };
	backWall.material.kd = 1.0f;
	backWall.material.ks = 0.01f;
	backWall.material.shininess = 25.0f;
	scene.objects.push_back(std::make_unique<Model>(backWall));

	Model floor2(Model::Type::Euclidean);
	floor1.vertices = { {9600, -100, 100, 1}, {9600, -100, -600, 1}, {10400, -100, 100, 1}, {10400, -100, -600, 1} };
	floor1.indices = { 0, 2, 1, 2, 3, 1 };
	floor1.material.albedo = { 0.0f, 1.0f, 0.0f };
	floor1.material.kd = 1.0f;
	floor1.material.ks = 0.01f;
	floor1.material.shininess = 25.0f;
	scene.objects.push_back(std::make_unique<Model>(floor1));
	/*********************************************************/

	/************************ Portals ************************/
	std::unique_ptr<Portal> portal { new Portal };
	portal->loadFromFile("resources/portal1.obj");
	scene.objects.push_back(std::move(portal));
	/*********************************************************/

	/************************* Lights ************************/
	Light sun1({ 0, -1, -1, 0.0f }, 50, { 1.0f, 1.0f, 0.0f }, Light::Type::Distant);
	scene.lights.push_back(sun1);

	Light l1({ -175, -25, -380, 0.0f }, 2000, { 1.0f, 1.0f, 1.0f }, Light::Type::Point);
	scene.lights.push_back(l1);

	/*********************************************************/

	return scene;
}

Scene Scene::createInfiniteTunnelScene()
{
	Scene scene;

	scene.name = "Infinite tunnel";

	/************************ Objects ************************/
	std::unique_ptr<Model> tunnel{ new Model(Model::Type::Euclidean) };
	tunnel->loadFromFile("resources/infiniteTunnel.obj");
	tunnel->material.loadFromFile("resources/phongMaterial.mtl");
	scene.objects.push_back(std::move(tunnel));
	/*********************************************************/

	/************************ Portals ************************/
	std::unique_ptr<Portal> frontPortal{ new Portal() };
	frontPortal->loadFromFile("resources/infinitePortal1.obj");
	scene.objects.push_back(std::move(frontPortal));

	std::unique_ptr<Portal> backPortal{ new Portal() };
	backPortal->loadFromFile("resources/infinitePortal2.obj");
	scene.objects.push_back(std::move(backPortal));
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

Scene Scene::createShortTunnelScene()
{
	Scene scene;
	scene.name = "Compressed tunnel";
	scene.floorLevel = -200;

	/************************ Objects ************************/
	std::unique_ptr<Model> floor{ new Model(Model::Type::Euclidean) };
	floor->loadFromFile("resources/tunnelFloor.obj");
	floor->material.loadFromFile("resources/diffuseMaterial.mtl");
	scene.objects.push_back(std::move(floor));


	std::unique_ptr<Model> tunnelOuter{ new Model(Model::Type::Euclidean) };
	tunnelOuter->loadFromFile("resources/tunnel.obj");
	tunnelOuter->material.loadFromFile("resources/phongMaterial.mtl");
	scene.objects.push_back(std::move(tunnelOuter));
	/*********************************************************/

	/************************* Tunnel ************************/
	std::unique_ptr<WarpedTunnel> tunnel{ new WarpedTunnel() };
	tunnel->loadFromFile("resources/shortTunnel.obj");
	scene.objects.push_back(std::move(tunnel));
	/*********************************************************/

	/************************* Lights ************************/
	Light l2({ 650, 70,-700, 1.0f }, 25000, { 1.0f, 1.0f, 1.0f }, Light::Type::Point);
	scene.lights.push_back(l2);

	Light l1({ 650, 70, 100, 1.0f }, 25000, { 1.0f, 1.0f, 1.0f }, Light::Type::Point);
	scene.lights.push_back(l1);

	Light sun({ 0, -1, 0, 0.0f }, 50, { 1.0f, 1.0f, 0.0f }, Light::Type::Distant);
	scene.lights.push_back(sun);
	/*********************************************************/

	return scene;
}

Scene Scene::createLongTunnelScene()
{
	Scene scene;
	scene.name = "Expanded tunnel";
	scene.floorLevel = -200;

	/************************ Objects ************************/
	std::unique_ptr<Model> floor{ new Model(Model::Type::Euclidean) };
	floor->loadFromFile("resources/tunnelFloor.obj");
	floor->material.loadFromFile("resources/diffuseMaterial.mtl");
	scene.objects.push_back(std::move(floor));

	std::unique_ptr<Model> tunnelOuter{ new Model(Model::Type::Euclidean) };
	tunnelOuter->loadFromFile("resources/tunnel.obj");
	tunnelOuter->material.loadFromFile("resources/phongMaterial.mtl");
	scene.objects.push_back(std::move(tunnelOuter));
	/*********************************************************/

	/************************* Tunnel ************************/
	std::unique_ptr<WarpedTunnel> tunnel{ new WarpedTunnel() };
	tunnel->loadFromFile("resources/longTunnel.obj");
	scene.objects.push_back(std::move(tunnel));
	/*********************************************************/

	/************************* Lights ************************/
	Light l2({ 650, 70,-700, 1.0f }, 25000, { 1.0f, 1.0f, 1.0f }, Light::Type::Point);
	scene.lights.push_back(l2);

	Light l1({ 650, 70, 100, 1.0f }, 25000, { 1.0f, 1.0f, 1.0f }, Light::Type::Point);
	scene.lights.push_back(l1);

	Light sun({ 0, -1, 0, 0.0f }, 50, { 1.0f, 1.0f, 0.0f }, Light::Type::Distant);
	scene.lights.push_back(sun);
	/*********************************************************/

	return scene;
}

Scene Scene::createShrinkScene()
{
	Scene scene;
	scene.name = "Shrinking tunnel";
	scene.floorLevel = -200;

	/************************ Objects ************************/
	std::unique_ptr<Model> floor{ new Model(Model::Type::Euclidean) };
	floor->loadFromFile("resources/tunnelFloor.obj");
	floor->material.loadFromFile("resources/diffuseMaterial.mtl");
	scene.objects.push_back(std::move(floor));

	std::unique_ptr<Model> tunnelOuter{ new Model(Model::Type::Euclidean) };
	tunnelOuter->loadFromFile("resources/shrinkTunnelOuter.obj");
	tunnelOuter->material.loadFromFile("resources/phongMaterial.mtl");
	scene.objects.push_back(std::move(tunnelOuter));
	/*********************************************************/

	/************************* Tunnel ************************/
	std::unique_ptr<ShrinkTunnel> tunnel{ new ShrinkTunnel() };
	tunnel->loadFromFile("resources/shrinkTunnel.obj");
	scene.objects.push_back(std::move(tunnel));
	/*********************************************************/

	/************************* Lights ************************/
	Light l2({ 650, 70,-700, 1.0f }, 25000, { 1.0f, 1.0f, 1.0f }, Light::Type::Point);
	scene.lights.push_back(l2);

	Light l1({ 650, 70, 100, 1.0f }, 25000, { 1.0f, 1.0f, 1.0f }, Light::Type::Point);
	scene.lights.push_back(l1);

	Light sun({ 0, -1, 0, 0.0f }, 50, { 1.0f, 1.0f, 0.0f }, Light::Type::Distant);
	scene.lights.push_back(sun);
	/*********************************************************/

	return scene;
}

Scene Scene::createRotatingTunnelScene()
{
	Scene scene;
	scene.name = "Rotating tunnel";
	scene.floorLevel = -200;

	/************************ Objects ************************/
	std::unique_ptr<Model> floor{ new Model(Model::Type::Euclidean) };
	floor->loadFromFile("resources/tunnelFloor.obj");
	floor->material.loadFromFile("resources/diffuseMaterial.mtl");
	scene.objects.push_back(std::move(floor));

	std::unique_ptr<Model> tunnelOuter{ new Model(Model::Type::Euclidean) };
	tunnelOuter->loadFromFile("resources/tunnel.obj");
	tunnelOuter->material.loadFromFile("resources/phongMaterial.mtl");
	scene.objects.push_back(std::move(tunnelOuter));
	/*********************************************************/

	/************************* Tunnel ************************/
	std::unique_ptr<RotationTunnel> tunnel{ new RotationTunnel() };
	tunnel->loadFromFile("resources/rotationTunnel1.obj");
	scene.objects.push_back(std::move(tunnel));
	/*********************************************************/

	/************************* Lights ************************/
	Light l2({ 650, 70,-700, 1.0f }, 25000, { 1.0f, 1.0f, 1.0f }, Light::Type::Point);
	scene.lights.push_back(l2);

	Light l1({ 650, 70, 100, 1.0f }, 25000, { 1.0f, 1.0f, 1.0f }, Light::Type::Point);
	scene.lights.push_back(l1);

	Light sun({ 0, -1, 0, 0.0f }, 50, { 1.0f, 1.0f, 0.0f }, Light::Type::Distant);
	scene.lights.push_back(sun);
	/*********************************************************/

	return scene;
}

Scene Scene::createRotatingTunnelScene2()
{
	Scene scene;
	scene.name = "Rotating tunnel 2";
	scene.floorLevel = -200;

	/************************ Objects ************************/
	std::unique_ptr<Model> floor{ new Model(Model::Type::Euclidean) };
	floor->loadFromFile("resources/tunnelFloor.obj");
	floor->material.loadFromFile("resources/diffuseMaterial.mtl");
	scene.objects.push_back(std::move(floor));

	std::unique_ptr<Model> tunnelOuter{ new Model(Model::Type::Euclidean) };
	tunnelOuter->loadFromFile("resources/rotateTunnelOuter.obj");
	tunnelOuter->material.loadFromFile("resources/phongMaterial.mtl");
	scene.objects.push_back(std::move(tunnelOuter));
	/*********************************************************/

	/************************* Tunnel ************************/
	std::unique_ptr<RotationTunnel> tunnel1{ new RotationTunnel() };
	tunnel1->loadFromFile("resources/rotationTunnel21.obj");
	scene.objects.push_back(std::move(tunnel1));

	std::unique_ptr<RotationTunnel> tunnel2{ new RotationTunnel() };
	tunnel2->loadFromFile("resources/rotationTunnel22.obj");
	scene.objects.push_back(std::move(tunnel2));
	/*********************************************************/

	/************************* Lights ************************/
	Light l2({ 650, 70,-700, 1.0f }, 25000, { 1.0f, 1.0f, 1.0f }, Light::Type::Point);
	scene.lights.push_back(l2);

	Light l1({ 650, 70, 100, 1.0f }, 25000, { 1.0f, 1.0f, 1.0f }, Light::Type::Point);
	scene.lights.push_back(l1);

	Light sun({ 0, -1, 0, 0.0f }, 50, { 1.0f, 1.0f, 0.0f }, Light::Type::Distant);
	scene.lights.push_back(sun);
	/*********************************************************/

	return scene;
}

void Scene::preProcessScene()
{
	// Model preprocessing
	for (auto& object : objects)
	{
		// Transform every vertex to world space
		for (auto& vertex : object->vertices)
		{
			vertex = object->toWorld * vertex;
		}

		// Primitive assembly
		object->assembleTriangles();

		// Construct bounding volume around object
		object->buildAABB();
	}
}
