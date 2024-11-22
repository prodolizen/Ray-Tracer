#pragma once
#include "GCP_GFX_Framework.h"
#include "Ray.h"
#include <cmath>
#include <iostream>
struct Intersect
{
	bool _happened;
	glm::vec3 _position;
};
class Sphere
{
private:
	glm::vec3 GetNormal(glm::vec3 input);

public:
	glm::vec3 _position;
	float _radius;
	Intersect RayIntersect(Ray ray);
	glm::vec3 Shade(glm::vec3 _intersection, glm::vec3 lightPos, glm::vec3 lightColour);
};

