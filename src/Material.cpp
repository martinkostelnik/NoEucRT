/**
 * @file Material.cpp
 * @author Martin Kostelník (xkoste12@stud.fit.vutbr.cz)
 * @brief Implementation file of the Material class.
 * @version 1.0
 * @date 2021-05-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "Material.hpp"

Material::Material(const glm::vec3 albedo) :
	albedo(albedo),
	shininess(0.0f),
	ks(0.0f),
	kd(0.0f),
	ka(0.0f)
{
}

Material::Material(const glm::vec3 albedo, const float shininess, const float ks, const float kd, const float ka) : 
	albedo(albedo),
	shininess(shininess),
	ks(ks),
	kd(kd),
	ka(ka)
{
}
