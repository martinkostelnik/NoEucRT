/**
 * @file Ray.cpp
 * @author Martin Kostelník (xkoste12@stud.fit.vutbr.cz)
 * @brief Implementation file of the Ray class.
 * @version 1.0
 * @date 2021-05-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "Ray.hpp"

Ray::Ray() :
    origin(0, 0, 0, 1),
    direction(0, 0, 0, 0)
{
}

Ray::Ray(const glm::vec4& direction) :
    origin(0, 0, 0, 1),
    direction(direction)
{
}

Ray::Ray(const glm::vec4& origin, const glm::vec4& direction) : 
    origin(origin),
    direction(direction)
{
}

/**
 * @brief Implementation was taken and modified from BUT FIT GPUEngine: https://github.com/Rendering-FIT/GPUEngine
 */
bool Ray::intersectsTriangle(const Triangle& triangle, float& out_distance, float* out_u, float* out_v) const
{
    const float EPSILON = 0.0000001;

    glm::vec3 origin3 = origin;
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

    //glm::vec3 s = origin3 - glm::vec3(triangle.v1);
    glm::vec3 s = { origin3.x - triangle.v1.x, origin3.y - triangle.v1.y, origin3.z - triangle.v1.z };

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
        if (out_u && out_v)
        {
            *out_u = u;
            *out_v = v;
        }
        out_distance = t;
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * @brief Implementation was taken and modified from: https://tavianator.com/2011/ray_box.html
 */
bool Ray::intersectsAABB(const AABB& aabb, float* const out_distance) const
{
    glm::vec3 invDir(1.0f / direction.x, 1.0f / direction.y, 1.0f / direction.z);

    float tx1 = (aabb.min.x - origin.x) * invDir.x;
    float tx2 = (aabb.max.x - origin.x) * invDir.x;

    float tmin = glm::min(tx1, tx2);
    float tmax = glm::max(tx1, tx2);

    float ty1 = (aabb.min.y - origin.y) * invDir.y;
    float ty2 = (aabb.max.y - origin.y) * invDir.y;

    tmin = glm::max(tmin, glm::min(ty1, ty2));
    tmax = glm::min(tmax, glm::max(ty1, ty2));

    float tz1 = (aabb.min.z - origin.z) * invDir.z;
    float tz2 = (aabb.max.z - origin.z) * invDir.z;

    tmin = glm::max(tmin, glm::min(tz1, tz2));
    tmax = glm::min(tmax, glm::max(tz1, tz2));

    return tmax >= glm::max(0.0f, tmin);
}

bool Ray::seesLight(const Light& light, const Scene& scene) const
{
    const float distance = glm::distance(light.position, { origin });
    float hitDistance = 0.0f;

    for (const auto& object : scene.objects)
    {
        if (object->type == Model::Type::WarpedTunnel || object->type == Model::Type::ShrinkTunnel || object->type == Model::Type::RotationTunnel)
            continue;

        if (intersectsAABB(object->boundingBox))
        {
            for (const auto& triangle : object->triangles)
            {
                if (intersectsTriangle(triangle, hitDistance)) // hitDistance is out parameter
                {
                    if (hitDistance < distance)
                    {
                        return false;
                    }
                }
            }
        }
    }

    return true;    
}
