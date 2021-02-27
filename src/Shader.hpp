#pragma once
#include <glm/glm.hpp>

class Shader
{
public:
	Shader();

private:
	virtual glm::vec3 getColor() = 0;
};
