#include "RayTracer.h"


glm::vec3 RayTracer::TraceRay(Ray ray, std::vector<Sphere> spheres, glm::vec3 _cameraPos)
{
    for (int i = 0; i < spheres.size(); i++) //cycle through all spheres in scene
    {
        Intersect _intersection = spheres[i].RayIntersect(ray);

        if (_intersection._happened) //if there is an intersection colour the pixel, break from the loop and then return the colour
        {
            pixelColour = spheres[i].Shade(_intersection._position, lightPos, lightColour, _cameraPos);
            break;
        }
        else
            pixelColour = glm::vec3(0, 0, 1); //if no intersection colour pixel to background colour
    }

    return pixelColour;
}

//glm::vec3 RayTracer::TraceRay(Ray ray, std::vector<Sphere> spheres, glm::vec3 _cameraPos)
//{
//    glm::vec3 pixelColour = glm::vec3(0, 0, 0); // Default color (background, no intersection)
//    float closestT = FLT_MAX; // Initialize with the maximum float value
//    int closestSphereIndex = -1; // To store the index of the closest sphere
//
//    for (int i = 0; i < spheres.size(); i++) // Cycle through all spheres in the scene
//    {
//        Intersect _intersection = spheres[i].RayIntersect(ray);
//
//        if (_intersection._happened) // If an intersection happens
//        {
//            // Calculate the distance to the intersection point
//            float t = glm::length(_intersection._position - ray._origin);
//
//            // If this intersection is closer than the previously found ones, update the closest intersection
//            if (t < closestT) {
//                closestT = t;
//                closestSphereIndex = i;
//            }
//        }
//    }
//
//    // If there was a closest sphere found, shade it
//    if (closestSphereIndex != -1) {
//        Intersect closestIntersection = spheres[closestSphereIndex].RayIntersect(ray);
//        pixelColour = spheres[closestSphereIndex].Shade(closestIntersection._position, lightPos, lightColour, _cameraPos);
//    }
//
//    return pixelColour;
//
//
//}


