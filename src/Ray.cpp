#include "Ray.hpp"

Ray::Ray() : origin(0, 0, 0, 1), direction(0, 0, 0, 0)
{
}

bool Ray::intersectsTriangle(const Triangle& triangle, float& out_distance)
{
    const float EPSILON = 0.0000001;

    glm::vec3 origin3 = glm::vec3(origin.x, origin.y, origin.z);
    glm::vec3 direction3 = glm::vec3(direction.x, direction.y, direction.z);

    glm::vec3 edge1 = triangle.v2 - triangle.v1;
    glm::vec3 edge2 = triangle.v3 - triangle.v1;

    glm::vec3 h = glm::cross(direction3, edge2);
    float a = glm::dot(edge1, h);

    if (a > -EPSILON && a < EPSILON)
    {
        return false;
    }

    float f = 1.0 / a;
    glm::vec3 s = direction3 - triangle.v1;
    float u = f * glm::dot(s, h);

    if (u < 0.0 || u > 1.0)
    {
        return false;
    }

    glm::vec3 q = glm::cross(s, edge1);
    float v = f * glm::dot(direction3, q);

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
