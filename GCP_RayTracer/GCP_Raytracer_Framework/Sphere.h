#pragma once
#include "GCP_GFX_Framework.h"
#include "Ray.h"
struct Intersect
{
	bool _happened;
	glm::vec3 _position;
};
class Sphere
{
private:
	glm::vec3 _position;

	glm::vec3 GetNormal(glm::vec3 input);

public:
	Intersect RayIntersect(Ray ray);
	glm::vec3 Shade(glm::vec3 _intersection);
};

