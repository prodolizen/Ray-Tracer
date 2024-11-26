#include "Camera.h"

Ray Camera::GetRay(glm::ivec2 _windowPos)
{




    Ray ray;

    ray._origin = glm::vec3(_windowPos.x, _windowPos.y, 0);
    ray._direction = glm::vec3(0, 0, -1); 

    return ray;
}

//near point vec 4 z = -1
//far point vec 4 z = +1
//w = 1
//convert winpos to -1 +1 range for x and y 
//multiply by inverse proj matrix 
// multiply by invverse view matrix 
//divide by w 
//create ray


void Camera::Init()
{
    _projMatrix = glm::perspective(glm::radians(45.0f), float(4 / 3), -100.0f, 100.0f);
    _viewMatrix = glm::mat4(1);
}

glm::ivec2 Camera::SendWinSize(glm::ivec2 winSize)
{
    return winSize;
}
