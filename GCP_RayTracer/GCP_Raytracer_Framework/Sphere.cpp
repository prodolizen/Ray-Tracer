#include "Sphere.h"

glm::vec3 Sphere::GetNormal(glm::vec3 input)
{
	return glm::normalize(input);
}

//Intersect Sphere::RayIntersect(Ray ray)
Intersect Sphere::RayIntersect(const Ray& ray) const
{
    Intersect _intersect;

    // Convert sphere center to glm::vec3 for consistency
    glm::vec3 P = _position;

    // ray origin to sphere center
    glm::vec3 aToP = P - ray._origin;

    // projection
    float projection = glm::dot(aToP, ray._direction);

    // shortest distance from ray origin to center of sphere
    glm::vec3 closestPointOnRay = ray._origin + projection * ray._direction;
    float d = glm::length(P - closestPointOnRay);

    //If d > radius, no intersection
    if (d > _radius) {
        _intersect._happened = false;
    }
    else
    {
        _intersect._happened = true;
    }

    float x = std::sqrt(_radius * _radius - d * d);

    //Calculate the intersection point
    _intersect._position = ray._origin + (projection - x) * ray._direction;

    return _intersect; 
}

//glm::vec3 Sphere::Shade(glm::vec3 _intersection, glm::vec3 lightPos, glm::vec3 lightColour)
//{
//    glm::vec3 N = glm::normalize(_intersection - _position);
//    glm::vec3 colour = glm::dot(lightPos, N) * lightColour * _colour;
//    return colour;
//}

//glm::vec3 Sphere::Shade(glm::vec3 _intersection, glm::vec3 lightPos, glm::vec3 lightColour, glm::vec3 cameraPos, bool inShadow)
glm::vec3 Sphere::Shade(const glm::vec3& _intersection, const glm::vec3& lightPos, const glm::vec3& lightColour, const glm::vec3& cameraPos, bool inShadow) const
{
    //surface norm at intersect
    glm::vec3 N = glm::normalize(_intersection - _position);

    //lamberts cosine law for calculating diffuse
    glm::vec3 L = glm::normalize(lightPos - _intersection); // intersect to light dir
    float NdotL = glm::max(glm::dot(N, L), 0.0f); 

    glm::vec3 diffuse;

    if (inShadow)
        diffuse = glm::vec3(0, 0, 0);
    else
        diffuse = NdotL * lightColour * _colour;

    //calculate specular lighting (phong)
    glm::vec3 V = glm::normalize(cameraPos - _intersection); // intersect to cam dir
    glm::vec3 H = glm::normalize(L + V); //half vec between light anc cam 
    float NdotH = glm::max(glm::dot(N, H), 0.0f);

    float shininess = 150.0f;

    //phong
    float specularFactor = pow(NdotH, shininess);
    glm::vec3 specular = specularFactor * lightColour;

    // cook torrance implementation
    //glm::vec3 specular = SpecularLighting(N, L, V, glm::vec3(1.04f, 1.04f, 1.04f), 1.0f);

    glm::vec3 ambient = 0.1f * _colour;
    glm::vec3 color = ambient + diffuse + specular;

    return color;
}


//cook torrance implementation
glm::vec3 Sphere::SpecularLighting(glm::vec3 N, glm::vec3 L, glm::vec3 V, glm::vec3 F0, float roughness) const
{
    //half vec between light and view dir
    glm::vec3 H = glm::normalize(L + V);

    float cosTheta = glm::max(glm::dot(N, H), 0.0f);
    glm::vec3 F = _lighting.fresnelSchlick(cosTheta, F0);

    float D = _lighting.DistributionGGX(N, H, roughness);

    float k = roughness * roughness / 2.0f;
    float G = _lighting.GeometrySmith(N, V, L, k);

    //calculate specular using cook torrance
    float denominator = 4.0f * glm::max(glm::dot(N, V), 0.0f) * glm::max(glm::dot(N, L), 0.0f) + 0.001f; // Small epsilon to avoid divide by zero
    glm::vec3 specular = (F * D * G) / denominator;

    return specular;
}

