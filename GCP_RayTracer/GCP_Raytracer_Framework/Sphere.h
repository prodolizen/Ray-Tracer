#pragma once
#include "GCP_GFX_Framework.h"
#include "Ray.h"
#include <cmath>
#include <iostream>
#include "Lighting.h"
struct Intersect
{
	bool _happened;
	glm::vec3 _position;
};
class Sphere
{
private:
	glm::vec3 GetNormal(glm::vec3 input);
	glm::vec3 SpecularLighting(glm::vec3 N, glm::vec3 L, glm::vec3 V, glm::vec3 F0, float roughness);
	Lighting _lighting;

public:
	glm::vec3 _position;
	float _radius;
	Intersect RayIntersect(Ray ray);
	//glm::vec3 Shade(glm::vec3 _intersection, glm::vec3 lightPos, glm::vec3 lightColour);
	glm::vec3 Shade(glm::vec3 _intersection, glm::vec3 lightPos, glm::vec3 lightColour, glm::vec3 cameraPos);
	glm::vec3 _colour; 
};

