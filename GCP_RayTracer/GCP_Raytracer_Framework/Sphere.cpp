#include "Sphere.h"

glm::vec3 Sphere::GetNormal(glm::vec3 input)
{
	return glm::normalize(input);
}

Intersect Sphere::RayIntersect(Ray ray)
{
	Intersect _intersect;

	_intersect._happened = true;
	//_intersect._position =;

	return _intersect;
}
