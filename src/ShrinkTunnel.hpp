#pragma once

#include "Model.hpp"

class ShrinkTunnel : public Model
{
public:
	ShrinkTunnel();

	glm::vec4 direction;
	float finalSize;
	float length;
};
