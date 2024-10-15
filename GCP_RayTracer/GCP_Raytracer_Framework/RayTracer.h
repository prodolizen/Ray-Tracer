#pragma once
#include <iostream>
#include "GCP_GFX_Framework.h"
#include "Ray.h"
#include "Sphere.h"
#include <vector>
class RayTracer
{
private:
	Sphere _sphere;
public:
	glm::vec3 TraceRay(Ray ray, Sphere sphere);
};

