#pragma once

#include <vector>

namespace Geode
{
    struct Material;
    struct Ray;
    struct RayHit;
    struct Sphere;

    struct World
    {
        std::vector<Material> Materials;
        std::vector<Sphere> Objects;
    };

    /*
     * Finds the closest point of intersection of the ray with any of the objects in the world
     * Returns true if such intersection point was found and fills the HitInfo with the information
     * about the hit point, otherwise returns false
     */
    bool TryIntersect(const World& World, const Ray& Ray, RayHit& HitInfo);
}
