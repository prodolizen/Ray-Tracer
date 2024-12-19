#include "Lighting.h"
glm::vec3 Lighting::fresnelSchlick(float cosTheta, glm::vec3 F0) const
{
	return F0 + (1.0f - F0) * pow(1.0f - cosTheta, 5.0f);
}

float Lighting::DistributionGGX(glm::vec3 N, glm::vec3 H, float a) const
{
	float a2 = a * a;
	float NdotH = glm::max(glm::dot(N, H), 0.0f);
	float NdotH2 = NdotH * NdotH;
	float nom = a2;
	float denom = (NdotH2 * (a2 - 1.0) + 1.0);
	denom = PI * denom * denom;

	return nom / denom;
}

float Lighting::GeometrySchlickGGX(float NdotV, float k) const
{
	float nom = NdotV;
	float denom = NdotV * (1.0 - k) + k;

	return nom / denom;
}

float Lighting::GeometrySmith(glm::vec3 N, glm::vec3 V, glm::vec3 L, float k) const
{
	float NdotV = glm::max(glm::dot(N, V), 0.0f);
	float NdotL = glm::max(glm::dot(N, L), 0.0f);
	float ggx1 = GeometrySchlickGGX(NdotV, k);
	float ggx2 = GeometrySchlickGGX(NdotL, k);

	return ggx1 * ggx2;
}
