#pragma once
#include <glm/glm.hpp>

class Shader
{
public:
	Shader();
	virtual glm::vec3 getColor() const = 0;
};
