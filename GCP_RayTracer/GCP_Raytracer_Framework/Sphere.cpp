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

    // Step 1: Compute vector P - a (from ray origin to sphere center)
    glm::vec3 aToP = P - ray._origin;

    // Step 2: Compute projection of (P - a) onto the ray's direction (n)
    float projection = glm::dot(aToP, ray._direction);

    // Step 3: Compute d (the shortest distance from the ray to the center of the sphere)
    glm::vec3 closestPointOnRay = ray._origin + projection * ray._direction;
    float d = glm::length(P - closestPointOnRay);

    // Step 4: If d > radius, no intersection
    if (d > _radius) {
        _intersect._happened = false;
    }
    else
    {
        _intersect._happened = true;
    }

    // Step 5: Calculate x (distance from closest point on ray to intersection point)
    float x = std::sqrt(_radius * _radius - d * d);

    // Step 6: Calculate the intersection point
    _intersect._position = ray._origin + (projection - x) * ray._direction;

    return _intersect;  // Ray intersects the sphere
}