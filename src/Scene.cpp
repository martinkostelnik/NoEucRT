/**
 * @file Scene.cpp
 * @author Martin Kostelník (xkoste12@stud.fit.vutbr.cz)
 * @brief Implementation file of the Scene class. All the textures used in the demo scenes are from https://cc0textures.com/.
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
	testingCube->texture.loadFromFile("resources/wall.jpg");
	scene.objects.push_back(std::move(testingCube));

	std::unique_ptr<Model> floor { new Model(Model::Type::Euclidean) };
	floor->loadFromFile("resources/floor.obj");
	floor->material.loadFromFile("resources/diffuseMaterial.mtl");
	floor->texture.loadFromFile("resources/tilesFloor.jpg");
	scene.objects.push_back(std::move(floor));
	/*********************************************************/

	/************************ Portals ************************/
	std::unique_ptr<Portal> portal { new Portal };
	portal->loadFromFile("resources/portal3d.obj");
	scene.objects.push_back(std::move(portal));
	/*********************************************************/

	/************************* Lights ************************/
	Light l1({ 100.0f, 100.0f, -150.0f, 1.0f }, 7000.0, { 1.0f, 1.0f, 1.0f }, Light::Type::Point);
	scene.lights.push_back(l1);

	Light sun1(glm::normalize(glm::vec4(-1.0f, -1.0f, -1.0f, 0.0f)), 80.0f, { 1.0f, 1.0f, 1.0f }, Light::Type::Distant);
	scene.lights.push_back(sun1);

	Light sun2(glm::normalize(glm::vec4(1.0f, -1.0f, 1.0f, 0.0f)), 80.0f, { 1.0f, 1.0f, 1.0f }, Light::Type::Distant);
	scene.lights.push_back(sun2);
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
	floor1->texture.loadFromFile("resources/tilesFloor2.jpg");
	scene.objects.push_back(std::move(floor1));

	std::unique_ptr<Model> floor2{ new Model(Model::Type::Euclidean) };
	floor2->loadFromFile("resources/portalFloor2.obj");
	floor2->material.loadFromFile("resources/diffuseMaterial.mtl");
	floor2->texture.loadFromFile("resources/tilesFloor2.jpg");
	scene.objects.push_back(std::move(floor2));

	std::unique_ptr<Model> midWall{ new Model(Model::Type::Euclidean) };
	midWall->loadFromFile("resources/simpleMidWall.obj");
	midWall->material.loadFromFile("resources/diffuseMaterial.mtl");
	midWall->texture.loadFromFile("resources/simplePortalTexture.jpg");
	scene.objects.push_back(std::move(midWall));

	std::unique_ptr<Model> frontWall{ new Model(Model::Type::Euclidean) };
	frontWall->loadFromFile("resources/simpleFrontWall.obj");
	frontWall->material.loadFromFile("resources/diffuseMaterial.mtl");
	frontWall->texture.loadFromFile("resources/simplePortalTexture.jpg");
	scene.objects.push_back(std::move(frontWall));

	std::unique_ptr<Model> backWall{ new Model(Model::Type::Euclidean) };
	backWall->loadFromFile("resources/simpleBackWall.obj");
	backWall->material.loadFromFile("resources/diffuseMaterial.mtl");
	backWall->texture.loadFromFile("resources/simplePortalTexture.jpg");
	scene.objects.push_back(std::move(backWall));
	/*********************************************************/

	/************************ Portals ************************/
	std::unique_ptr<Portal> portal { new Portal };
	portal->loadFromFile("resources/portal1.obj");
	scene.objects.push_back(std::move(portal));
	/*********************************************************/

	/************************* Lights ************************/
	Light sun1(glm::normalize(glm::vec4(-1.0f, -1.0f, -1.0f, 0.0f)), 200.0f, { 1.0f, 1.0f, 1.0f }, Light::Type::Distant);
	scene.lights.push_back(sun1);

	Light sun2(glm::normalize(glm::vec4(1.0f, -1.0f, 1.0f, 0.0f)), 200.0f, { 1.0f, 1.0f, 1.0f }, Light::Type::Distant);
	scene.lights.push_back(sun2);

	Light l2({ 10000.0f, 100.0f, -250.0f, 0.0f }, 20000.0f, { 1.0f, 1.0f, 1.0f }, Light::Type::Point);
	scene.lights.push_back(l2);
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
	tunnel->texture.loadFromFile("resources/rock.jpg");
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
	Light l1({ -200.0f, 0.0f, -400.0f, 0.0f }, 15000.0f, { 1.0f, 1.0f, 1.0f }, Light::Type::Point);
	scene.lights.push_back(l1);

	Light l2({ 200.0f, 0.0f, -400.0f, 0.0f }, 15000.0f, { 1.0f, 1.0f, 1.0f }, Light::Type::Point);
	scene.lights.push_back(l2);
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
	floor->material.loadFromFile("resources/phongMaterial.mtl");
	floor->texture.loadFromFile("resources/tiles.jpg");
	scene.objects.push_back(std::move(floor));

	std::unique_ptr<Model> tunnelFront{ new Model(Model::Type::Euclidean) };
	tunnelFront->loadFromFile("resources/tunnelFront.obj");
	tunnelFront->material.loadFromFile("resources/phongMaterial.mtl");
	tunnelFront->texture.loadFromFile("resources/tiles3.jpg");
	scene.objects.push_back(std::move(tunnelFront));

	std::unique_ptr<Model> tunnelBack{ new Model(Model::Type::Euclidean) };
	tunnelBack->loadFromFile("resources/tunnelBack.obj");
	tunnelBack->material.loadFromFile("resources/phongMaterial.mtl");
	tunnelBack->texture.loadFromFile("resources/tiles3.jpg");
	scene.objects.push_back(std::move(tunnelBack));

	std::unique_ptr<Model> tunnelOuter{ new Model(Model::Type::Euclidean) };
	tunnelOuter->loadFromFile("resources/tunnelOuter.obj");
	tunnelOuter->material.loadFromFile("resources/phongMaterial.mtl");
	tunnelOuter->texture.loadFromFile("resources/tiles3.jpg");
	scene.objects.push_back(std::move(tunnelOuter));

	std::unique_ptr<Model> tunnelIn{ new Model(Model::Type::Euclidean) };
	tunnelIn->loadFromFile("resources/tunnelIn.obj");
	tunnelIn->material.loadFromFile("resources/phongMaterial.mtl");
	tunnelIn->texture.loadFromFile("resources/tiles3.jpg");
	scene.objects.push_back(std::move(tunnelIn));
	/*********************************************************/

	/************************* Tunnel ************************/
	std::unique_ptr<WarpedTunnel> tunnel{ new WarpedTunnel() };
	tunnel->loadFromFile("resources/shortTunnel.obj");
	scene.objects.push_back(std::move(tunnel));
	/*********************************************************/

	/************************* Lights ************************/
	Light l1({ 650.0f, 55.0f, 100.0f, 1.0f }, 10000.0f, { 1.0f, 1.0f, 1.0f }, Light::Type::Point);
	scene.lights.push_back(l1);

	Light l2({ 650.0f, 55.0f, -700.0f, 1.0f }, 10000.0f, { 1.0f, 1.0f, 1.0f }, Light::Type::Point);
	scene.lights.push_back(l2);

	Light sun1(glm::normalize(glm::vec4(-1.0f, -1.0f, -1.0f, 0.0f)), 200.0f, { 1.0f, 1.0f, 1.0f }, Light::Type::Distant);
	scene.lights.push_back(sun1);

	Light sun2(glm::normalize(glm::vec4(1.0f, -1.0f, 1.0f, 0.0f)), 200.0f, { 1.0f, 1.0f, 1.0f }, Light::Type::Distant);
	scene.lights.push_back(sun2);
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
	floor->material.loadFromFile("resources/phongMaterial.mtl");
	floor->texture.loadFromFile("resources/tiles.jpg");
	scene.objects.push_back(std::move(floor));

	std::unique_ptr<Model> tunnelFront{ new Model(Model::Type::Euclidean) };
	tunnelFront->loadFromFile("resources/tunnelFront.obj");
	tunnelFront->material.loadFromFile("resources/phongMaterial.mtl");
	tunnelFront->texture.loadFromFile("resources/tiles3.jpg");
	scene.objects.push_back(std::move(tunnelFront));

	std::unique_ptr<Model> tunnelBack{ new Model(Model::Type::Euclidean) };
	tunnelBack->loadFromFile("resources/tunnelBack.obj");
	tunnelBack->material.loadFromFile("resources/phongMaterial.mtl");
	tunnelBack->texture.loadFromFile("resources/tiles3.jpg");
	scene.objects.push_back(std::move(tunnelBack));

	std::unique_ptr<Model> tunnelOuter{ new Model(Model::Type::Euclidean) };
	tunnelOuter->loadFromFile("resources/tunnelOuter.obj");
	tunnelOuter->material.loadFromFile("resources/phongMaterial.mtl");
	tunnelOuter->texture.loadFromFile("resources/tiles3.jpg");
	scene.objects.push_back(std::move(tunnelOuter));

	std::unique_ptr<Model> tunnelIn{ new Model(Model::Type::Euclidean) };
	tunnelIn->loadFromFile("resources/tunnelIn.obj");
	tunnelIn->material.loadFromFile("resources/phongMaterial.mtl");
	tunnelIn->texture.loadFromFile("resources/tiles3.jpg");
	scene.objects.push_back(std::move(tunnelIn));
	/*********************************************************/

	/************************* Tunnel ************************/
	std::unique_ptr<WarpedTunnel> tunnel{ new WarpedTunnel() };
	tunnel->loadFromFile("resources/longTunnel.obj");
	scene.objects.push_back(std::move(tunnel));
	/*********************************************************/

	/************************* Lights ************************/
	Light l1({ 650.0f, 55.0f, 100.0f, 1.0f }, 10000.0f, { 1.0f, 1.0f, 1.0f }, Light::Type::Point);
	scene.lights.push_back(l1);

	Light l2({ 650.0f, 55.0f, -700.0f, 1.0f }, 10000.0f, { 1.0f, 1.0f, 1.0f }, Light::Type::Point);
	scene.lights.push_back(l2);

	Light sun1(glm::normalize(glm::vec4(-1.0f, -1.0f, -1.0f, 0.0f)), 200.0f, { 1.0f, 1.0f, 1.0f }, Light::Type::Distant);
	scene.lights.push_back(sun1);

	Light sun2(glm::normalize(glm::vec4(1.0f, -1.0f, 1.0f, 0.0f)), 200.0f, { 1.0f, 1.0f, 1.0f }, Light::Type::Distant);
	scene.lights.push_back(sun2);
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
	floor->texture.loadFromFile("resources/rocks2.jpg");
	scene.objects.push_back(std::move(floor));

	std::unique_ptr<Model> tunnelFront{ new Model(Model::Type::Euclidean) };
	tunnelFront->loadFromFile("resources/shrinkTunnelFront.obj");
	tunnelFront->material.loadFromFile("resources/phongMaterial.mtl");
	tunnelFront->texture.loadFromFile("resources/bricks.jpg");
	scene.objects.push_back(std::move(tunnelFront));

	std::unique_ptr<Model> tunnelBack{ new Model(Model::Type::Euclidean) };
	tunnelBack->loadFromFile("resources/shrinkTunnelBack.obj");
	tunnelBack->material.loadFromFile("resources/phongMaterial.mtl");
	tunnelBack->texture.loadFromFile("resources/bricks.jpg");
	scene.objects.push_back(std::move(tunnelBack));

	std::unique_ptr<Model> tunnelOuter{ new Model(Model::Type::Euclidean) };
	tunnelOuter->loadFromFile("resources/shrinkTunnelOuter.obj");
	tunnelOuter->material.loadFromFile("resources/phongMaterial.mtl");
	tunnelOuter->texture.loadFromFile("resources/bricks.jpg");
	scene.objects.push_back(std::move(tunnelOuter));

	std::unique_ptr<Model> tunnelIn{ new Model(Model::Type::Euclidean) };
	tunnelIn->loadFromFile("resources/shrinkTunnelIn.obj");
	tunnelIn->material.loadFromFile("resources/phongMaterial.mtl");
	tunnelIn->texture.loadFromFile("resources/bricks.jpg");
	scene.objects.push_back(std::move(tunnelIn));
	/*********************************************************/

	/************************* Tunnel ************************/
	std::unique_ptr<ShrinkTunnel> tunnel{ new ShrinkTunnel() };
	tunnel->loadFromFile("resources/shrinkTunnel.obj");
	scene.objects.push_back(std::move(tunnel));
	/*********************************************************/

	/************************* Lights ************************/
	Light l1({ 650.0f, 70.0f, 100.0f, 1.0f }, 10000.0f, { 1.0f, 1.0f, 1.0f }, Light::Type::Point);
	scene.lights.push_back(l1);

	Light sun1(glm::normalize(glm::vec4(-1.0f, -1.0f, -1.0f, 0.0f)), 200.0f, { 1.0f, 1.0f, 1.0f }, Light::Type::Distant);
	scene.lights.push_back(sun1);

	Light sun2(glm::normalize(glm::vec4(1.0f, -1.0f, 1.0f, 0.0f)), 200.0f, { 1.0f, 1.0f, 1.0f }, Light::Type::Distant);
	scene.lights.push_back(sun2);
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
	floor->texture.loadFromFile("resources/rocks4.jpg");
	scene.objects.push_back(std::move(floor));

	std::unique_ptr<Model> tunnelFront{ new Model(Model::Type::Euclidean) };
	tunnelFront->loadFromFile("resources/tunnelFront.obj");
	tunnelFront->material.loadFromFile("resources/phongMaterial.mtl");
	tunnelFront->texture.loadFromFile("resources/wall.jpg");
	scene.objects.push_back(std::move(tunnelFront));

	std::unique_ptr<Model> tunnelBack{ new Model(Model::Type::Euclidean) };
	tunnelBack->loadFromFile("resources/tunnelBack.obj");
	tunnelBack->material.loadFromFile("resources/phongMaterial.mtl");
	tunnelBack->texture.loadFromFile("resources/wall.jpg");
	scene.objects.push_back(std::move(tunnelBack));

	std::unique_ptr<Model> tunnelOuter{ new Model(Model::Type::Euclidean) };
	tunnelOuter->loadFromFile("resources/tunnelOuter.obj");
	tunnelOuter->material.loadFromFile("resources/phongMaterial.mtl");
	tunnelOuter->texture.loadFromFile("resources/wall.jpg");
	scene.objects.push_back(std::move(tunnelOuter));

	std::unique_ptr<Model> tunnelIn{ new Model(Model::Type::Euclidean) };
	tunnelIn->loadFromFile("resources/tunnelIn.obj");
	tunnelIn->material.loadFromFile("resources/phongMaterial.mtl");
	tunnelIn->texture.loadFromFile("resources/wall.jpg");
	scene.objects.push_back(std::move(tunnelIn));
	/*********************************************************/

	/************************* Tunnel ************************/
	std::unique_ptr<RotationTunnel> tunnel{ new RotationTunnel() };
	tunnel->loadFromFile("resources/rotationTunnel1.obj");
	scene.objects.push_back(std::move(tunnel));
	/*********************************************************/

	/************************* Lights ************************/
	Light l1({ 650.0f, 70.0f, 100.0f, 1.0f }, 10000.0f, { 1.0f, 1.0f, 1.0f }, Light::Type::Point);
	scene.lights.push_back(l1);

	Light sun1(glm::normalize(glm::vec4(-1.0f, -1.0f, -1.0f, 0.0f)), 200.0f, { 1.0f, 1.0f, 1.0f }, Light::Type::Distant);
	scene.lights.push_back(sun1);

	Light sun2(glm::normalize(glm::vec4(1.0f, -1.0f, 1.0f, 0.0f)), 200.0f, { 1.0f, 1.0f, 1.0f }, Light::Type::Distant);
	scene.lights.push_back(sun2);
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
	floor->texture.loadFromFile("resources/rocks4.jpg");
	scene.objects.push_back(std::move(floor));

	std::unique_ptr<Model> tunnelFront{ new Model(Model::Type::Euclidean) };
	tunnelFront->loadFromFile("resources/rotateTunnelFront.obj");
	tunnelFront->material.loadFromFile("resources/phongMaterial.mtl");
	tunnelFront->texture.loadFromFile("resources/wall.jpg");
	scene.objects.push_back(std::move(tunnelFront));

	std::unique_ptr<Model> tunnelBack{ new Model(Model::Type::Euclidean) };
	tunnelBack->loadFromFile("resources/rotateTunnelBack.obj");
	tunnelBack->material.loadFromFile("resources/phongMaterial.mtl");
	tunnelBack->texture.loadFromFile("resources/wall.jpg");
	scene.objects.push_back(std::move(tunnelBack));

	std::unique_ptr<Model> tunnelOuter{ new Model(Model::Type::Euclidean) };
	tunnelOuter->loadFromFile("resources/rotateTunnelOuter.obj");
	tunnelOuter->material.loadFromFile("resources/phongMaterial.mtl");
	tunnelOuter->texture.loadFromFile("resources/wall.jpg");
	scene.objects.push_back(std::move(tunnelOuter));

	std::unique_ptr<Model> tunnelIn{ new Model(Model::Type::Euclidean) };
	tunnelIn->loadFromFile("resources/rotateTunnelIn.obj");
	tunnelIn->material.loadFromFile("resources/phongMaterial.mtl");
	tunnelIn->texture.loadFromFile("resources/wall.jpg");
	scene.objects.push_back(std::move(tunnelIn));
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
	Light l1({ 650.0f, 70.0f, 100.0f, 1.0f }, 10000.0f, { 1.0f, 1.0f, 1.0f }, Light::Type::Point);
	scene.lights.push_back(l1);

	Light sun1(glm::normalize(glm::vec4(-1.0f, -1.0f, -1.0f, 0.0f)), 200.0f, { 1.0f, 1.0f, 1.0f }, Light::Type::Distant);
	scene.lights.push_back(sun1);

	Light sun2(glm::normalize(glm::vec4(1.0f, -1.0f, 1.0f, 0.0f)), 200.0f, { 1.0f, 1.0f, 1.0f }, Light::Type::Distant);
	scene.lights.push_back(sun2);
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
