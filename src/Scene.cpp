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

Scene::Scene() :
	objects(),
	mainCamera(),
	skybox("resources/skybox.png"),
	floorLevel(0.0f)
{
}

Scene Scene::create3DPortalScene()
{
	Scene scene;
	scene.name = "3D Portal scene";
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

	/************************ Portals ************************/
	std::unique_ptr<Portal> portal { new Portal };
	portal->loadFromFile("resources/portal3d.obj");
	scene.objects.push_back(std::move(portal));
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

	scene.name = "Simple portal scene";
	scene.floorLevel = -100.0;

	/************************ Objects ************************/
	std::unique_ptr<Model> floor1{ new Model(Model::Type::Euclidean) };
	floor1->loadFromFile("resources/portalFloor1.obj");
	floor1->material.loadFromFile("resources/diffuseMaterial.mtl");
	scene.objects.push_back(std::move(floor1));

	std::unique_ptr<Model> floor2{ new Model(Model::Type::Euclidean) };
	floor2->loadFromFile("resources/portalFloor2.obj");
	floor2->material.loadFromFile("resources/diffuseMaterial.mtl");
	scene.objects.push_back(std::move(floor2));

	std::unique_ptr<Model> midWall{ new Model(Model::Type::Euclidean) };
	midWall->loadFromFile("resources/simpleMidWall.obj");
	midWall->material.loadFromFile("resources/diffuseMaterial.mtl");
	scene.objects.push_back(std::move(midWall));

	std::unique_ptr<Model> frontWall{ new Model(Model::Type::Euclidean) };
	frontWall->loadFromFile("resources/simpleFrontWall.obj");
	frontWall->material.loadFromFile("resources/diffuseMaterial.mtl");
	scene.objects.push_back(std::move(frontWall));

	std::unique_ptr<Model> backWall{ new Model(Model::Type::Euclidean) };
	backWall->loadFromFile("resources/simpleBackWall.obj");
	backWall->material.loadFromFile("resources/diffuseMaterial.mtl");
	scene.objects.push_back(std::move(backWall));
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
