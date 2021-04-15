#pragma once

#include "Model.hpp"

#include <glm/glm.hpp>

class WarpedTunnel : public Model
{
public:
	WarpedTunnel();

	glm::vec4 direction;
	float intensity;
};
