#include "Model.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

Model::Model() :
	toWorld(1.0f),
	albedo(1.0f, 0.0f, 0.0f)
{
}

Model::Model(const std::string fileName) :
	toWorld(1.0f),
	albedo(1.0f, 0.0f, 0.0f)
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

void Model::constructBVH()
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

void Model::loadFromFile(std::string fileName)
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

		if (type == "v" || type == "V") // Reading vertex
		{
			float x = 0.0,
				  y = 0.0,
			      z = 0.0;

			lineStream >> x >> y >> z;
			vertices.push_back({ x, y, z, 1 });
		}
		else if (type == "f" || type == "F") // Reading face
		{
			std::string f1, f2, f3;

			lineStream >> f1 >> f2 >> f3;

			indices.push_back(stoi(f1) - 1);
			indices.push_back(stoi(f2) - 1);
			indices.push_back(stoi(f3) - 1);
		}
		else if (type == "vn") // Reading vertex normal
		{
			float x = 0.0,
				  y = 0.0,
				  z = 0.0;

			lineStream >> x >> y >> z;
			vertexNormals.push_back({ x, y, z });
		}
	}
	fileHandle.close();
}
