#include "RayTracer.h"


glm::vec3 RayTracer::TraceRay(Ray ray, Sphere sphere)
{
    //TODO: when multiple objects in scene we need to go through each ones RayInstersect() and see which is closest then only Shade() that one
    // remove vec3 store in new intersect
    Intersect _intersection = sphere.RayIntersect(ray); //intersect position (intersect struct val)

    if (_intersection._happened)
    {
        glm::vec3 colour = sphere.Shade(_intersection._position);
        return colour;
    }
    else
        return glm::vec3(0, 0, 1);
}
