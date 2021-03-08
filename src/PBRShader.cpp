#include "PBRShader.hpp"
#include <glm/gtx/norm.hpp>
#include <iostream>
#include "glm/gtx/string_cast.hpp"

PBRShader::PBRShader()
{
}

glm::vec3 PBRShader::getColor(const Ray& primaryRay, const Scene& scene, const Model& hitModel, const Triangle& hitTriangle, const float& distance) const
{
    const glm::vec3 hitPoint = primaryRay.origin + glm::normalize(primaryRay.direction) * distance;

    const glm::vec3 edge1 = { hitTriangle.v2.x - hitTriangle.v1.x, hitTriangle.v2.y - hitTriangle.v1.y, hitTriangle.v2.z - hitTriangle.v1.z };
    const glm::vec3 edge2 = { hitTriangle.v3.x - hitTriangle.v1.x, hitTriangle.v3.y - hitTriangle.v1.y, hitTriangle.v3.z - hitTriangle.v1.z };
    
    const glm::vec3 hitNormal = glm::normalize(glm::cross(edge1, edge2));
    
    glm::vec3 hitColor(0.0f);

    for (const auto& light : scene.lights)
    {
        glm::vec3 lightDirection = light.position - hitPoint;
        glm::vec3 lightAmount = light.intensity * light.color / (4 * glm::pi<float>() * glm::length2(lightDirection));

        Ray shadowRay({ hitPoint, 1.0f }, { lightDirection, 0.0f });

        hitColor += float(shadowRay.seesLight(light, scene)) * hitModel.albedo * lightAmount * std::max(0.0f, glm::dot(hitNormal, glm::normalize(lightDirection)));
    }

    return glm::clamp(hitColor, { 0.0f }, { 255.0f });
}
