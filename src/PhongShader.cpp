#include "PhongShader.hpp"

#include <glm/gtx/norm.hpp>

PhongShader::PhongShader()
{
}

glm::vec3 PhongShader::getColor(const Ray& ray, const Scene& scene, const glm::vec4& hitPoint, const Model& hitModel, const Triangle& hitTriangle) const
{
    glm::vec3 hitColor(0.0f);

    const glm::vec3 edge1 = { hitTriangle.v2.x - hitTriangle.v1.x, hitTriangle.v2.y - hitTriangle.v1.y, hitTriangle.v2.z - hitTriangle.v1.z };
    const glm::vec3 edge2 = { hitTriangle.v3.x - hitTriangle.v1.x, hitTriangle.v3.y - hitTriangle.v1.y, hitTriangle.v3.z - hitTriangle.v1.z };

    const glm::vec4 hitNormal = { glm::normalize(glm::cross(edge1, edge2)), 0.0f };

    glm::vec3 diffuse(0.0f);
    glm::vec3 specular(0.0f);

    #pragma omp parallel for
    for (int i = 0; i < scene.lights.size(); i++)
    {
        glm::vec4 lightDirection;
        glm::vec3 lightAmount;

        switch (scene.lights[i].type)
        {
        case Light::Type::Distant:
            lightDirection = -scene.lights[i].position;
            lightAmount = scene.lights[i].intensity * scene.lights[i].color;
            break;

        case Light::Type::Point:
            lightDirection = scene.lights[i].position - hitPoint;
            lightAmount = scene.lights[i].intensity * scene.lights[i].color * 1e4f / (4 * glm::pi<float>() * glm::length2(lightDirection));
            break;
        }

        const float bias = 0.001f;
        Ray shadowRay(hitPoint + hitNormal * bias, glm::normalize(lightDirection));
        float visible = float(shadowRay.seesLight(scene.lights[i], scene));

        glm::vec3 R = glm::normalize(glm::reflect(glm::normalize(-lightDirection), hitNormal));

        diffuse += visible * hitModel.material.albedo * lightAmount * glm::max(0.0f, glm::dot(hitNormal, glm::normalize(lightDirection)));
        specular += visible * lightAmount * glm::pow(glm::max(0.0f, glm::dot(R, { -ray.direction })), hitModel.material.shininess);
    }
        
    hitColor = diffuse * hitModel.material.kd + specular * hitModel.material.ks;

    return glm::clamp(hitColor, 0.0f, 255.0f);
}
