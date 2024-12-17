#include "Camera.h"

Ray Camera::GetRay(glm::ivec2 _windowPos)
{
    Ray ray;

    float xNorm = ((2.0f * (float)_windowPos.x) / (float)_windowSize.x) - 1.0f; //convert x pixel position to -1, 1 range
    float yNorm = ((2.0f * (float)_windowPos.y) / (float)_windowSize.y) - 1.0f; //convert y pixel position to -1, 1 range
    //float w = 1.0f;
    //glm::vec4 normalisedCoords = glm::vec4(xNorm, yNorm, -1, 1); //create vec4
   // normalisedCoords = glm::inverse(_projMatrix) * normalisedCoords; //multiply by inversed proj matrix
    //normalisedCoords = glm::inverse(_viewMatrix) * normalisedCoords; //multiply by inversed view matrix

    glm::vec4 nearPlane = glm::vec4(xNorm, yNorm, -1.0f, 1.0f);

    nearPlane = glm::inverse(_projMatrix) * nearPlane;
    nearPlane = glm::inverse(_viewMatrix) * nearPlane;
    nearPlane /= nearPlane.w;

    glm::vec4 farPlane = glm::vec4(xNorm, yNorm, 1.0f, 1.0f);

    farPlane = glm::inverse(_projMatrix) * farPlane;

    farPlane = glm::inverse(_viewMatrix) * farPlane;
    //farPlane = glm::vec4(farPlane.x, farPlane.y, 1.0f, farPlane.w);
    farPlane /= farPlane.w;

    glm::vec3 dir = glm::vec3(farPlane.x, farPlane.y, farPlane.z) - glm::vec3(nearPlane.x, nearPlane.y, nearPlane.z);
    glm::vec3 normDir = glm::normalize(dir);

    ray._origin = glm::vec3(nearPlane.x, nearPlane.y, nearPlane.z);
    ray._direction = normDir;

    //ray._origin = glm::vec3(normalisedCoords.x, normalisedCoords.y, normalisedCoords.z);
    
    /*ray._origin = glm::vec3(_windowPos.x, _windowPos.y, 0);
    ray._direction = glm::vec3(0, 0, -1); */
    /*std::cout << "near plane: " << nearPlane.x << ", " << nearPlane.y << ", " << nearPlane.z << std::endl;
    std::cout << "far plane: " << farPlane.x << ", " << farPlane.y << ", " << farPlane.z << std::endl;

    std::cout << "X norm: " << xNorm << std::endl;
    std::cout << "Y norm: " << yNorm << std::endl;
    std::cout << "Ray Origin: " << ray._origin.x << ", " << ray._origin.y << ", " << ray._origin.z << std::endl;
    std::cout << "Ray Direction: " << ray._direction.x << ", " << ray._direction.y << ", " << ray._direction.z << std::endl;*/

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
    _projMatrix = glm::perspective(glm::radians(45.0f), float(4.0f / 3.0f), 0.1f, 100.0f);
    _viewMatrix = glm::mat4(1);
}

glm::ivec2 Camera::SendWinSize(glm::ivec2 winSize)
{
    _windowSize = winSize;
    return winSize;
}
