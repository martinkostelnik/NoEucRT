#include "Scene.hpp"
#include <glm/gtc/matrix_transform.hpp>

Scene::Scene() :
	objects(),
	mainCamera()
{
	Model testingCube;
	testingCube.vertices = { {-100, -100, -100, 1}, {0, -100, -100, 1}, {0, 0, -100, 1}, {-100, 0, -100, 1},
							 {-100, -100, -200, 1}, {0, -100, -200, 1}, {0, 0, -200, 1}, {-100, 0, -200, 1} };
	testingCube.indices = {0, 1, 2, 0, 2, 3, 0, 3, 4, 3, 7, 4, 6, 5, 4, 4, 7, 6, 1, 5, 2, 2, 5, 6, 0, 4, 1, 1, 4, 5, 2, 7, 3, 2, 6, 7};
	objects.push_back(testingCube);

	Model floor;
	floor.vertices = { {10000, -200, 10000, 1}, {10000, -200, -10000, 1}, {-10000, -200, -10000, 1}, {-10000, -200, 10000, 1}};
	floor.indices = {0, 1, 2, 0, 2, 3};
	objects.push_back(floor);

	/*Model teapot("teapot.obj");
	teapot.toWorld = glm::scale(teapot.toWorld, { 100, 100, 100 });
	objects.push_back(teapot);*/

	/*Model armadillo("armadillo.obj");
	armadillo.toWorld = glm::scale(armadillo.toWorld, { 100, 100, 100 });
	objects.push_back(armadillo);*/

	/*Model cow("cow.obj");
	cow.toWorld = glm::scale(cow.toWorld, { 100, 100, 100 });
	objects.push_back(cow);*/

	/*Model dragon("dragon.obj");
	dragon.toWorld = glm::scale(dragon.toWorld, { 100, 100, 100 });
	objects.push_back(dragon);*/

	/*Model donut("donut.obj");
	donut.toWorld = glm::scale(donut.toWorld, { 100, 100, 100 });
	objects.push_back(donut);*/

	Light l({ 0, 100, 0 }, 500000000, { 1.0f, 1.0f, 1.0f });
	lights.push_back(l);

	Light l2({ 150, 100, -500 }, 500000000, { 1.0f, 1.0f, 1.0f });
	lights.push_back(l2);
}
