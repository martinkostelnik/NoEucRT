/**
 * @file Model.cpp
 * @author Martin Kostelník (xkoste12@stud.fit.vutbr.cz)
 * @brief Implementation file of the Model class.
 * @version 1.0
 * @date 2021-05-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "Model.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

Model::Model() :
	toWorld(1.0f),
	material(Material({ 0.0f, 1.0f, 0.0f })),
	type(Model::Type::Euclidean)
{
}

Model::Model(const Type type) :
	toWorld(1.0f),
	material(Material({ 0.0f, 1.0f, 0.0f })),
	type(type)
{
}

Model::Model(const std::string fileName) :
	toWorld(1.0f),
	material(Material({ 1.0f, 0.0f, 0.0f })),
	type(Model::Type::Euclidean)
{
	loadFromFile(fileName);
}

void Model::assembleTriangles()
{
	triangles.reserve(indices.size() / 3);

	for (size_t i = 0; i < indices.size(); i += 3)
	{
		triangles.emplace_back(vertices[indices[i]], vertices[indices[i + 1]], vertices[indices[i + 2]]);
	}
}

void Model::buildAABB()
{
	for (const auto& vertex : vertices)
	{
		if (vertex.x < boundingBox.min.x)
		{
			boundingBox.min.x = vertex.x;
		}
		if (vertex.y < boundingBox.min.y)
		{
			boundingBox.min.y = vertex.y;
		}
		if (vertex.z < boundingBox.min.z)
		{
			boundingBox.min.z = vertex.z;
		}
		if (vertex.x > boundingBox.max.x)
		{
			boundingBox.max.x = vertex.x;
		}
		if (vertex.y > boundingBox.max.y)
		{
			boundingBox.max.y = vertex.y;
		}
		if (vertex.z > boundingBox.max.z)
		{
			boundingBox.max.z = vertex.z;
		}
	}
}

void Model::loadFromFile(const std::string fileName)
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

		if (type == "v") // Reading vertex
		{
			float x = 0.0f;
			float y = 0.0f;
			float z = 0.0f;

			lineStream >> x >> y >> z;
			vertices.push_back(glm::vec4(x, y, z, 1.0f));
		}
		else if (type == "vt") // Reading texture coordinate
		{
			float x = 0.0f;
			float y = 0.0f;

			lineStream >> x >> y;
			textureCoordinates.push_back(glm::vec2(x, y));
		}
		else if (type == "f") // Reading face
		{
			std::string values[3];

			lineStream >> values[0] >> values[1] >> values[2];
			for (size_t i = 0; i < 3; i++)
			{
				size_t delPos = values[i].find('/');

				if (delPos == std::string::npos) // Char / not found, we have no texture coordinates
				{
					indices.push_back(size_t(stoi(values[i])) - 1);
				}
				else // Load texture coordinates as well
				{
					size_t vIndex = size_t(stoi(values[i].substr(0, delPos))) - 1;
					size_t tIndex = size_t(stoi(values[i].substr(delPos + 1))) - 1;
					indices.push_back(vIndex);
					textureCoordinateMapping.insert({ &vertices[vIndex], &textureCoordinates[tIndex] });
				}
			}
		}
	}

	fileHandle.close();
}

void Model::loadNonEuclideanData(const std::string fileName)
{
}
