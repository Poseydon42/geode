#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace Geode
{
    struct Ray;
    struct RayHit;

    struct Sphere
    {
        glm::vec3 Position;
        float Radius;

        size_t MaterialIndex;
    };

    /*
     * Returns true if there exists the point of intersection of the ray with the sphere
     * If such points exists, fills the hit info parameter with the information about the closest point of intersection
     * between the sphere and the ray
     */
    bool TryIntersect(const Sphere& Sphere, const Ray& Ray, RayHit& HitInfo);
} // namespace Geode
