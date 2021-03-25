#pragma once 

#include <glm/glm.hpp>

class Material
{
public:
	Material(const glm::vec3 albedo);
	glm::vec3 albedo;

	Material(const glm::vec3 albedo, const float shininess, const float ks, const float kd, const float ka);
	float shininess;
	float ka;
	float kd;
	float ks;
};
