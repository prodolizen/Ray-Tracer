#include "Camera.h"

Ray Camera::GetRay(glm::ivec2 _windowPos)
{
    Ray ray;

    ray._origin = glm::ivec3(_windowPos.x, _windowPos.y, 0);
    //ray._direction = 

    return ray;
}

glm::ivec2 Camera::SendWinSize(glm::ivec2 winSize)
{
    return winSize;
}
