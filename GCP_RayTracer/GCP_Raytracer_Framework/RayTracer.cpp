#include "RayTracer.h"


glm::vec3 RayTracer::TraceRay(Ray ray, std::vector<Sphere> spheres, glm::vec3 _cameraPos)
{
    for (int i = 0; i < spheres.size(); i++) //cycle through all spheres in scene
    {
        Intersect _intersection = spheres[i].RayIntersect(ray);

        if (_intersection._happened) //if there is an intersection colour the pixel, break from the loop and then return the colour
        {
            //calculate whether a shadow should appear
            Ray shadowRay; 
            shadowRay._origin = _intersection._position;
            shadowRay._direction = glm::normalize(lightPos - _intersection._position);
            Intersect shadowIntersect;

            for (int x = 0; x < spheres.size(); x++) //re go through all spheres
            {
                if (i == x) //ignore the current sphere we are looking at 
                    continue;

                else
                {
                    shadowIntersect = spheres[x].RayIntersect(shadowRay);
                    pixelColour = spheres[i].Shade(_intersection._position, lightPos, lightColour, _cameraPos, shadowIntersect._happened);
                    break;
                }
            }


           // pixelColour = spheres[i].Shade(_intersection._position, lightPos, lightColour, _cameraPos);
           break;
        }
        else
            pixelColour = glm::vec3(0, 0, 0); //if no intersection colour pixel to background colour
    }

    return pixelColour;
}


