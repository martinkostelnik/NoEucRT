/**
 * @file ShrinkTunnel.cpp
 * @author Martin Kostelník (xkoste12@stud.fit.vutbr.cz)
 * @brief Implementation file of the ShrinkTunnel class.
 * @version 1.0
 * @date 2021-05-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "ShrinkTunnel.hpp"

#include <fstream>
#include <sstream>

ShrinkTunnel::ShrinkTunnel() :
	direction(0.0f),
	finalSize(0.0f),
	length(0.0f),
	ceiling(0.0f)
{
	type = Model::Type::ShrinkTunnel;
}

void ShrinkTunnel::loadFromFile(const std::string fileName)
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
			glm::vec4 vertex{ 0.0f, 0.0f, 0.0f, 1.0f };

			lineStream >> vertex.x >> vertex.y >> vertex.z;
			vertices.push_back(vertex);
		}
		else if (type == "f") // Reading face
		{
			std::string values[3];

			lineStream >> values[0] >> values[1] >> values[2];
			for (size_t i = 0; i < 3; i++)
			{
				indices.push_back(size_t(stoi(values[i])) - 1);
			}
		}
		else if (type == "d")
		{
			glm::vec4 d{ 0.0f, 0.0f, 0.0f, 0.0f };

			lineStream >> d.x >> d.y >> d.z;
			direction = d;
		}
		else if (type == "i")
		{
			float i = 0.0f;

			lineStream >> i;
			finalSize = i;
		}
		else if (type == "c")
		{
			float c = 0.0f;

			lineStream >> c;
			ceiling = c;
		}
		else if (type == "l")
		{
			float l = 0.0f;

			lineStream >> l;
			length = l;
		}
	}

	fileHandle.close();
}
