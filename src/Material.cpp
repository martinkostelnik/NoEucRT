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

#include <fstream>
#include <sstream>
#include <algorithm>

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

void Material::loadFromFile(const std::string fileName)
{
	std::ifstream fileHandle;
	fileHandle.open(fileName);

	if (!fileHandle)
		return;

	std::string line;

	while (std::getline(fileHandle, line))
	{
		std::istringstream lineStream(line);
		std::string type;

		lineStream >> type;

		// Convert to lowercase
		std::transform(type.begin(), type.end(), type.begin(), [](unsigned char c) { return std::tolower(c); });

		if (type == "ks")
		{
			lineStream >> ks;
		}
		else if (type == "kd")
		{
			lineStream >> kd;
		}
		else if (type == "ka")
		{
			lineStream >> ka;
		}
		else if (type == "ns")
		{
			lineStream >> shininess;
		}
	}

	fileHandle.close();
}
