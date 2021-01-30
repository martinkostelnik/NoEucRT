#include "Ray.hpp"

Ray::Ray() : origin(0, 0, 0, 1), direction(0, 0, 0, 0)
{
}

Ray::Ray(const glm::vec4 direction) : origin(0, 0, 0, 1), direction(direction)
{
}

bool Ray::intersectsTriangle(const Triangle& triangle, float& out_distance) const
{
    const float EPSILON = 0.0000001;

    glm::vec3 direction3 = direction;

    glm::vec3 edge1 = { triangle.v2.x - triangle.v1.x, triangle.v2.y - triangle.v1.y, triangle.v2.z - triangle.v1.z };
    glm::vec3 edge2 = { triangle.v3.x - triangle.v1.x, triangle.v3.y - triangle.v1.y, triangle.v3.z - triangle.v1.z };

    //glm::vec3 h = glm::cross(direction3, edge2);
    glm::vec3 h = { direction3.y * edge2.z - direction3.z * edge2.y,
                    direction3.z * edge2.x - direction3.x * edge2.z,
                    direction3.x * edge2.y - direction3.y * edge2.x};

    //float a = glm::dot(edge1, h);
    float a = edge1.x * h.x + edge1.y * h.y + edge1.z * h.z;

    if (a > -EPSILON && a < EPSILON)
    {
        return false;
    }

    float f = 1.0 / a;

    //glm::vec3 s = direction3 - glm::vec3(triangle.v1);
    glm::vec3 s = { direction3.x - triangle.v1.x, direction3.y - triangle.v1.y, direction3.z - triangle.v1.z };

    //float u = f * glm::dot(s, h);
    float u = f * (s.x * h.x + s.y * h.y + s.z * h.z);

    if (u < 0.0 || u > 1.0)
    {
        return false;
    }

    //glm::vec3 q = glm::cross(s, edge1);
    glm::vec3 q = { s.y * edge1.z - s.z * edge1.y,
                    s.z * edge1.x - s.x * edge1.z,
                    s.x * edge1.y - s.y * edge1.x };

    //float v = f * glm::dot(direction3, q);
    float v = f * (direction3.x * q.x + direction3.y * q.y + direction3.z * q.z);

    if (v < 0.0 || u + v > 1.0)
    {
        return false;
    }

    //float t = f * glm::dot(edge2, q);
    float t = f * (edge2.x * q.x + edge2.y * q.y + edge2.z * q.z);

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
