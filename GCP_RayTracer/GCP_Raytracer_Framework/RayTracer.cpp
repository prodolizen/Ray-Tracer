#include "RayTracer.h"


glm::vec3 RayTracer::TraceRay(Ray ray, Sphere sphere)
{

    //TODO: when multiple objects in scene we need to go through each ones RayInstersect() and see which is closest then only Shade() that one
    glm::vec3 _intersectionPos = sphere.RayIntersect(ray)._position;
    glm::vec3 colour = sphere.Shade(_intersectionPos);
    return colour;
}
