#include "Skybox.hpp"
#include <iostream>

// 700 x 525 (175 x 175 squares)
Skybox::Skybox(const std::string fileName)
{
    cubeMap.loadFromFile(fileName);
    faceSize = cubeMap.getSize().x / 4;

    mapping.reserve(6);
    mapping.emplace_back(faceSize * 2, faceSize * 2 - 1); // 0 - right face
    mapping.emplace_back(0, faceSize * 2 - 1); // 1 - left face
    mapping.emplace_back(faceSize, faceSize - 1); // 2 - top face
    mapping.emplace_back(faceSize, faceSize * 3 - 1); // 3 - bot face
    mapping.emplace_back(faceSize, faceSize * 2 - 1); // 4 - front face
    mapping.emplace_back(faceSize * 3, faceSize * 2 - 1); // 5 - back face
}

sf::Color Skybox::getColor(const glm::vec4& rayDirection) const
{
    float absX = fabs(rayDirection.x);
    float absY = fabs(rayDirection.y);
    float absZ = fabs(rayDirection.z);

    int isXPositive = rayDirection.x > 0 ? 1 : 0;
    int isYPositive = rayDirection.y > 0 ? 1 : 0;
    int isZPositive = -rayDirection.z > 0 ? 1 : 0;

    float maxAxis = 0.0f;
    float u = 0.0f;
    float v = 0.0f;
    size_t index = 0;

    // POSITIVE X
    if (isXPositive && absX >= absY && absX >= absZ) {
        // u (0 to 1) goes from +z to -z
        // v (0 to 1) goes from -y to +y
        maxAxis = absX;
        u = rayDirection.z;
        v = rayDirection.y;
        index = 0;
    }
    // NEGATIVE X
    else if (!isXPositive && absX >= absY && absX >= absZ) {
        // u (0 to 1) goes from -z to +z
        // v (0 to 1) goes from -y to +y
        maxAxis = absX;
        u = -rayDirection.z;
        v = rayDirection.y;
        index = 1;
    }
    // POSITIVE Y
    else if (isYPositive && absY >= absX && absY >= absZ) {
        // u (0 to 1) goes from -x to +x
        // v (0 to 1) goes from +z to -z
        maxAxis = absY;
        u = rayDirection.x;
        v = rayDirection.z;
        index = 2;
    }
    // NEGATIVE Y
    else if (!isYPositive && absY >= absX && absY >= absZ) {
        // u (0 to 1) goes from -x to +x
        // v (0 to 1) goes from -z to +z
        maxAxis = absY;
        u = rayDirection.x;
        v = -rayDirection.z;
        index = 3;
    }
    // POSITIVE Z
    else if (isZPositive && absZ >= absX && absZ >= absY) {
        // u (0 to 1) goes from -x to +x
        // v (0 to 1) goes from -y to +y
        maxAxis = absZ;
        u = rayDirection.x;
        v = rayDirection.y;
        index = 4;
    }
    // NEGATIVE Z
    else if (!isZPositive && absZ >= absX && absZ >= absY) {
        // u (0 to 1) goes from +x to -x
        // v (0 to 1) goes from -y to +y
        maxAxis = absZ;
        u = -rayDirection.x;
        v = rayDirection.y;
        index = 5;
    }

    // Convert range from -1 to 1 to 0 to 1
    u = 0.5f * (u / maxAxis + 1.0f);
    v = 0.5f * (v / maxAxis + 1.0f);
    
    size_t x = mapping[index].x + u * (faceSize - 1);
    size_t y = mapping[index].y - v * (faceSize - 1);

	return cubeMap.getPixel(x, y);
}
