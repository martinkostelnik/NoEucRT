#include "Ray.hpp"

Ray::Ray() : origin(0, 0, 0, 1), direction(0, 0, 0, 0)
{
}

bool Ray::intersectsTriangle(const Triangle& triangle, float& out_distance)
{
    const float EPSILON = 0.0000001;

    glm::vec3 rayOrigin = { this->origin.x, this->origin.y, this->origin.z };
    glm::vec3 rayDirection = { this->direction.x, this->direction.y, this->direction.z };

    glm::vec3 edge1 = triangle.v2 - triangle.v1;
    glm::vec3 edge2 = triangle.v3 - triangle.v1;

    glm::vec3 h = glm::cross(rayDirection, edge2);
    float a = glm::dot(edge1, h);

    if (a > -EPSILON && a < EPSILON)
    {
        return false;
    }

    float f = 1.0 / a;
    glm::vec3 s = rayOrigin - triangle.v1;
    float u = f * glm::dot(s, h);

    if (u < 0.0 || u > 1.0)
    {
        return false;
    }

    glm::vec3 q = glm::cross(s, edge1);
    float v = f * glm::dot(rayDirection, q);

    if (v < 0.0 || u + v > 1.0)
    {
        return false;
    }

    float t = f * glm::dot(edge2, q);

    if (t > EPSILON)
    {
        out_distance = t;
        return true;
    }
    else
    {
        return false;
    }
}
