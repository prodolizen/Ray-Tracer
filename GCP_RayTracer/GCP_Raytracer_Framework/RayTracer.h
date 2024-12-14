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
	glm::vec3 lightPos;
	glm::vec3 lightColour; 
	glm::vec3 TraceRay(Ray ray, std::vector<Sphere> spheres, glm::vec3 _cameraPos);
	std::vector<Sphere> spheres;
	glm::vec3 pixelColour;
};

