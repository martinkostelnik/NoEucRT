#include "Scene.hpp"

Scene::Scene() :
	objects(),
	mainCamera()
{
	/************************ Objects ************************/
	Model testingCube;
	testingCube.vertices = { {-100, -100, -100, 1}, {0, -100, -100, 1}, {0, 0, -100, 1}, {-100, 0, -100, 1},
							 {-100, -100, -200, 1}, {0, -100, -200, 1}, {0, 0, -200, 1}, {-100, 0, -200, 1} };
	testingCube.indices = {0, 1, 2, 0, 2, 3, 0, 3, 4, 3, 7, 4, 6, 5, 4, 4, 7, 6, 1, 5, 2, 2, 5, 6, 0, 4, 1, 1, 4, 5, 2, 7, 3, 2, 6, 7};
	testingCube.material.albedo = { 1.0f, 0.0f, 0.0f };
	testingCube.material.shininess = 50.0f;
	testingCube.material.kd = 1.0f;
	testingCube.material.ks = 0.04f;
	objects.push_back(testingCube);

	Model floor;
	floor.vertices = { {10000, -200, 10000, 1}, {10000, -200, -10000, 1}, {-10000, -200, -10000, 1}, {-10000, -200, 10000, 1}};
	floor.indices = {0, 1, 2, 0, 2, 3};
	floor.material.albedo = { 0.0f, 1.0f, 0.0f };
	floor.material.kd = 1.0f;
	floor.material.ks = 0.01f;
	floor.material.shininess = 25.0f;
	objects.push_back(floor);
	/*********************************************************/

	/************************* Lights ************************/
	Light l({ 0, 100, 0 }, 25000, { 0.0f, 0.0f, 1.0f }, Light::Type::Point);
	lights.push_back(l);

	Light l2({ 150, 100, -500 }, 25000, { 1.0f, 1.0f, 1.0f }, Light::Type::Point);
	lights.push_back(l2);

	//Light sun({ 0, -1, 0 }, 50, { 1.0f, 1.0f, 0.0f }, Light::Type::Distant);
	//lights.push_back(sun);
	/*********************************************************/
}
