#include "Sphere.h"

glm::vec3 Sphere::GetNormal(glm::vec3 input)
{
	return glm::normalize(input);
}

Intersect Sphere::RayIntersect(Ray ray)
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

glm::vec3 Sphere::Shade(glm::vec3 _intersection)
{
    glm::vec3 N = GetNormal(_intersection);

    return glm::vec3(1,0,0);
}
