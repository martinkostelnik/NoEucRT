#include "Scene.hpp"

/************ DELETE THIS ************/
#include <iostream>
#include <glm/gtx/string_cast.hpp>
/*************************************/

#include "Portal.hpp"
#include "WarpedTunnel.hpp"

Scene::Scene() :
	objects(),
	mainCamera(),
	skybox("skybox.png")
{
}

Scene Scene::createBaseScene()
{
	Scene scene;
	scene.name = "Basic scene";

	/************************ Objects ************************/
	/*Model testingCube(Model::Type::Euclidean);
	testingCube.vertices = { {-100, -100, -100, 1}, {0, -100, -100, 1}, {0, 100, -100, 1}, {-100, 100, -100, 1},
							 {-100, -100, -200, 1}, {0, -100, -200, 1}, {0, 100, -200, 1}, {-100, 100, -200, 1} };
	testingCube.indices = { 0, 1, 2, 0, 2, 3, 0, 3, 4, 3, 7, 4, 6, 5, 4, 4, 7, 6, 1, 5, 2, 2, 5, 6, 0, 4, 1, 1, 4, 5, 2, 7, 3, 2, 6, 7 };
	testingCube.material.albedo = { 1.0f, 0.0f, 0.0f };
	testingCube.material.shininess = 50.0f;
	testingCube.material.kd = 1.0f;
	testingCube.material.ks = 0.04f;
	scene.objects.push_back(std::make_unique<Model>(testingCube));*/

	Model floor(Model::Type::Euclidean);
	floor.vertices = { {10000, -200, 10000, 1}, {10000, -200, -10000, 1}, {-10000, -200, -10000, 1}, {-10000, -200, 10000, 1} };
	floor.indices = { 0, 1, 2, 0, 2, 3 };
	floor.material.albedo = { 0.0f, 1.0f, 0.0f };
	floor.material.kd = 1.0f;
	floor.material.ks = 0.01f;
	floor.material.shininess = 25.0f;
	scene.objects.push_back(std::make_unique<Model>(floor));

	Model TunnelOuter(Model::Type::Euclidean);
	TunnelOuter.vertices = { { 500, 100, 0, 1 }, { 800, 100, 0, 1 }, { 500, 100, -600, 1 }, { 800, 100, -600, 1}, // Top Inner corners
						     { 500, -200, 0, 1 }, { 800, -200, 0, 1 }, { 500, -200, -600, 1 }, { 800, -200, -600, 1}, // Bot Inner corners
							 { 467, -200, 0, 1 }, { 833, -200, 0, 1 }, { 467, -200, -600, 1 }, { 833, -200, -600, 1 }, // Bot outer corners
							 { 467, 133, 0, 1 }, { 833, 133, 0, 1 }, { 467, 133, -600, 1 }, { 833, 133, -600, 1 }, // Top outer corners
							 { 500, 133, 0, 1 }, { 800, 133, 0, 1 }, { 500, 133, -600, 1 }, { 800, 133, -600, 1 } }; // Help vertices
	TunnelOuter.indices = { 2, 0, 4, 2, 4, 6, 1, 3, 7, 1, 7, 5, 1, 0, 2, 1, 2, 3, 8, 12, 10, 12, 14, 10, 9, 15, 13, 9, 11, 15, 12, 13, 14, 13, 15, 14,
							8, 4, 12, 4, 16, 12, 5, 9, 17, 9, 13, 17, 0, 1, 16, 1, 17, 16, 6, 10, 18, 10, 14, 18, 11, 7, 15, 7, 19, 15, 3, 2, 19, 2, 18, 19};
	TunnelOuter.material.albedo = { 0.0f, 0.0f, 1.0f };
	TunnelOuter.material.kd = 1.0f;
	floor.material.ks = 0.0f;
	floor.material.shininess = 0.0f;
	scene.objects.push_back(std::make_unique<Model>(TunnelOuter));
	/*********************************************************/

	/************************* Tunnel ************************/
	WarpedTunnel tunnel;
	tunnel.vertices = { {495, -205, -5, 1 }, { 805, -205, -5, 1 }, { 495, 105, -5, 1 }, { 805, 105, -5, 1 },
					  { 495, -205, -595, 1 }, { 805, -205, -595, 1 }, { 495, 105, -595, 1 }, { 805, 105, -595, 1 } };
	tunnel.indices = { 0, 1, 2, 1, 3, 2, 4, 0, 2, 4, 2, 6, 5, 4, 6, 5, 6, 7, 5, 3, 1, 5, 7, 3, 6, 2, 7, 2, 3, 7, 5, 1, 0, 4, 5, 0 };
	tunnel.direction = { 0.0f, 0.0f, -1.0f, 0.0f };
	tunnel.intensity = 0.0f;
	scene.objects.push_back(std::make_unique<WarpedTunnel>(tunnel));

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

	/************************ Objects ************************/
	Model floor1(Model::Type::Euclidean);
	floor1.vertices = { {-400, -100, 100, 1}, {-400, -100, -600, 1}, {400, -100, 100, 1}, {400, -100, -600, 1} };
	floor1.indices = { 0, 2, 1, 2, 3, 1 };
	floor1.material.albedo = { 0.0f, 1.0f, 0.0f };
	floor1.material.kd = 1.0f;
	floor1.material.ks = 0.001f;
	floor1.material.shininess = 15.0f;
	scene.objects.push_back(std::make_unique<Model>(floor1));

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
	Portal portal;
	portal.vertices = { { -50.0f, -100.0f, -400.0f, 1 }, {-50.0f, 50.0f, -400.0f, 1 }, { 50.0f, -100.0f, -400.0f, 1 }, { 50.0f, 50.0f, -400.0f, 1 } };
	portal.indices = { 0, 2, 1, 2, 3, 1 };
	portal.center = (portal.vertices[0] + portal.vertices[3]) / 2.0f;
	portal.exit = { 10000.0f, 0.0f, 0.0f, 1.0f };
	scene.objects.push_back(std::make_unique<Portal>(portal));
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
	Model floor(Model::Type::Euclidean);
	floor.vertices = { {400, -200, 350, 1}, {400, -200, -1150, 1}, {-400, -200, -1150, 1}, {-400, -200, 350, 1} };
	floor.indices = { 0, 1, 2, 0, 2, 3 };
	floor.material.albedo = { 0.0f, 1.0f, 0.0f };
	floor.material.kd = 1.0f;
	floor.material.ks = 0.0f;
	floor.material.shininess = 25.0f;
	scene.objects.push_back(std::make_unique<Model>(floor));

	Model leftWall(Model::Type::Euclidean);
	leftWall.vertices = { {-400, -200, 350, 1}, {-400, -200, -1150, 1}, {-400, 200, 350, 1}, {-400, 200, -1150, 1} };
	leftWall.indices = { 0, 1, 2, 1, 3, 2 };
	leftWall.material.albedo = { 0.0f, 1.0f, 0.0f };
	leftWall.material.kd = 1.0f;
	leftWall.material.ks = 0.0f;
	leftWall.material.shininess = 25.0f;
	scene.objects.push_back(std::make_unique<Model>(leftWall));

	Model topWall(Model::Type::Euclidean);
	topWall.vertices = { {-400, 200, 350, 1}, {400, 200, 350, 1}, {-400, 200, -1150, 1}, {400, 200, -1150, 1} };
	topWall.indices = { 0, 2, 1, 1, 2, 3 };
	topWall.material.albedo = { 0.0f, 1.0f, 0.0f };
	topWall.material.kd = 1.0f;
	topWall.material.ks = 0.01f;
	topWall.material.shininess = 25.0f;
	scene.objects.push_back(std::make_unique<Model>(topWall));

	Model rightWall(Model::Type::Euclidean);
	rightWall.vertices = { {400, -200, 350, 1}, {400, -200, -1150, 1}, {400, 200, 350, 1}, {400, 200, -1150, 1} };
	rightWall.indices = { 0, 2, 1, 1, 2, 3 };
	rightWall.material.albedo = { 0.0f, 1.0f, 0.0f };
	rightWall.material.kd = 1.0f;
	rightWall.material.ks = 0.0f;
	rightWall.material.shininess = 25.0f;
	scene.objects.push_back(std::make_unique<Model>(rightWall));
	/*********************************************************/

	/************************ Portals ************************/
	Portal frontPortal;
	frontPortal.vertices = { { -400.0f, -200.0f, -1150.0f, 1 }, {400.0f, -200.0f, -1150.0f, 1 }, { -400.0f, 200.0f, -1150.0f, 1 }, { 400.0f, 200.0f, -1150.0f, 1 } };
	frontPortal.indices = { 0, 1, 2, 1, 3, 2 };
	frontPortal.center = (frontPortal.vertices[0] + frontPortal.vertices[3]) / 2.0f;
	frontPortal.exit = { 0.0f, 0.0f, 300.0f, 1.0f };
	scene.objects.push_back(std::make_unique<Portal>(frontPortal));

	Portal backPortal;
	backPortal.vertices = { { -400.0f, -200.0f, 350.0f, 1 }, {400.0f, -200.0f, 350.0f, 1 }, { -400.0f, 200.0f, 350.0f, 1 }, { 400.0f, 200.0f, 350.0f, 1 } };
	backPortal.indices = { 0, 2, 1, 1, 2, 3};
	backPortal.center = (backPortal.vertices[1] + backPortal.vertices[2]) / 2.0f;
	backPortal.exit = { 0.0f, 0.0f, -1100.0f, 1.0f };
	scene.objects.push_back(std::make_unique<Portal>(backPortal));
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
