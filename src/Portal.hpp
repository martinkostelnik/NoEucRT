#pragma once

#include "Model.hpp"

#include <glm/glm.hpp>

class Portal : public Model
{
public:
	Portal();

	glm::vec4 exit;
};
