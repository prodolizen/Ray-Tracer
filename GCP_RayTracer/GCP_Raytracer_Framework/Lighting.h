#pragma once
#include "GCP_GFX_Framework.h"
class Lighting
{
public:
	float DistributionGGX(glm::vec3 N, glm::vec3 H, float a) const;
	glm::vec3 fresnelSchlick(float cosTheta, glm::vec3 F0) const;
	float GeometrySchlickGGX(float NdotV, float k) const;
	float GeometrySmith(glm::vec3 N, glm::vec3 V, glm::vec3 L, float k) const;
	float shininess = 50.0f;
	float alpha = 1.0f;
	float roughness = 1.0f;
	glm::vec3 specularColour = glm::vec3(0, 1, 0);

private:
	float PI = 3.14f;
};

