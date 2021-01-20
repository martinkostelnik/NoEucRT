#pragma once

#include <glm/glm.hpp>

class Triangle
{
public:
	Triangle(const glm::vec4& v1, const glm::vec4& v2, const glm::vec4& v3);

	const glm::vec4& v1;
	const glm::vec4& v2;
	const glm::vec4& v3;
};
