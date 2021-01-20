#include "Model.hpp"

Model::Model()
{
}

void Model::assembleTriangles()
{
	triangles.reserve(indices.size() / 3);

	for (size_t i = 0; i < indices.size(); i += 3)
	{
		triangles.emplace_back(vertices[indices[i]], vertices[indices[i + 1]], vertices[indices[i + 2]]);
	}
}
