#include "Model.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

Model::Model() : toWorld(1.0f)
{
}

Model::Model(const std::string fileName)
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
	}
	fileHandle.close();
}
