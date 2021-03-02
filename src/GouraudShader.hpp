#pragma once

#include <glm/glm.hpp>
#include "Shader.hpp"

class GouraudShader : public Shader
{
public:
	glm::vec3 getColor() const;
};
