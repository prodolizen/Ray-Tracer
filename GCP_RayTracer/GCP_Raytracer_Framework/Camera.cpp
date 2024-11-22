#include "Camera.h"

Ray Camera::GetRay(glm::ivec2 _windowPos)
{
    Ray ray;

    ray._origin = glm::vec3(_windowPos.x, _windowPos.y, 0);
    ray._direction = glm::vec3(0, 0, -1); 

    return ray;
}

glm::ivec2 Camera::SendWinSize(glm::ivec2 winSize)
{
    return winSize;
}
