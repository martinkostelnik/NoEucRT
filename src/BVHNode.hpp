#pragma once
#include "Model.hpp"
#include "AABB.hpp"

class BVHNode
{
public:
	BVHNode();

	BVHNode* leftChild;
	BVHNode* rightChild;
	Model* model;
	AABB boundingBox;
};
