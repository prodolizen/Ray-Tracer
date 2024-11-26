#pragma once
#include "GCP_GFX_Framework.h"
#include "Ray.h"
#include "GLM/ext.hpp"
class Camera
{
private:
	glm::ivec2 _windowSize;
	glm::mat4 _viewMatrix;
	glm::mat4 _projMatrix;
	glm::mat4 _modelMatrix;


public:
	glm::ivec2 SendWinSize(glm::ivec2 winSize);
	Ray GetRay(glm::ivec2 _windowPos);
	void Init();
	glm::vec3 _Position;
};

