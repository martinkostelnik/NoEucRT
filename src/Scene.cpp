#include "Scene.hpp"

Scene::Scene() : objects(), mainCamera()
{
	/*Model testingTriangle;
	testingTriangle.vertices = { {0, 0, -500, 1}, {50, 0, -500, 1}, {0, 50, -500, 1} };
	testingTriangle.indices = {0, 1, 2};
	objects.push_back(testingTriangle);

	Model testingSquare;
	testingSquare.vertices = { {-100, -100, -100, 1}, {0, -100, -100, 1}, {0, 0, -100, 1}, {-100, 0, -100, 1}};
	testingSquare.indices = { 0, 1, 2, 0, 2, 3 };
	objects.push_back(testingSquare);*/

	Model testingCube;
	testingCube.vertices = { {-100, -100, -100, 1}, {0, -100, -100, 1}, {0, 0, -100, 1}, {-100, 0, -100, 1},
							 {-100, -100, -200, 1}, {0, -100, -200, 1}, {0, 0, -200, 1}, {-100, 0, -200, 1} };
	testingCube.indices = {0, 1, 2, 0, 2, 3, 0, 4, 3, 3, 4, 7, 4, 5, 6, 4, 6, 7, 1, 2, 5, 2, 5, 6, 0, 1, 4, 1, 4, 5, 2, 3, 7, 2, 6, 7};
	objects.push_back(testingCube);

	for (auto& model : objects)
	{
		model.assembleTriangles();
	}
}
