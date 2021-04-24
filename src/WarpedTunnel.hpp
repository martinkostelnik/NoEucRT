#pragma once

#include "Model.hpp"

class WarpedTunnel : public Model
{
public:
	WarpedTunnel();

	glm::vec4 warpDirection;
	glm::vec4 moveDirection;
	float intensity;
};
