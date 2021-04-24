#pragma once

#include "Model.hpp"

class RotationTunnel : public Model
{
public:
	RotationTunnel();

	glm::vec4 direction;
	float maxRotation;
	float length;
};
