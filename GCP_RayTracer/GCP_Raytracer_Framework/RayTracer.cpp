#include "RayTracer.h"


glm::vec3 RayTracer::TraceRay(Ray ray, std::vector<Sphere> spheres)
{
    //TODO: when multiple objects in scene we need to go through each ones RayInstersect() and see which is closest then only Shade() that one
    // remove vec3 store in new intersect
    //Intersect _intersection = sphere.RayIntersect(ray); //intersect position (intersect struct val)

    //if (_intersection._happened)
    //{
    //    glm::vec3 colour = sphere.Shade(_intersection._position, lightPos, lightColour);
    //    return colour;
    //}
    //else
    //    return glm::vec3(0, 0, 1);

    for (int i = 0; i < spheres.size(); i++) //cycle through all spheres in scene
    {
        Intersect _intersection = spheres[i].RayIntersect(ray);

        if (_intersection._happened) //if there is an intersection colour the pixel, break from the loop and then return the colour
        {
            pixelColour = spheres[i].Shade(_intersection._position, lightPos, lightColour);
            break;
        }
        else
            pixelColour = glm::vec3(0, 0, 1); //if no intersection colour pixel to background colour
    }

    return pixelColour;
}
