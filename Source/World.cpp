#include "World.h"

#include <numeric>

#include "Ray.h"
#include "Surface.h"

namespace Geode
{
    bool TryIntersect(const World& World, const Ray& Ray, RayHit& HitInfo)
    {
        bool Result = false;
        float ClosestDistance = std::numeric_limits<float>::max();

        for (const auto& Object : World.Objects)
        {
            RayHit CurrentHit = {};
            if (TryIntersect(Object, Ray, CurrentHit) && CurrentHit.Distance < ClosestDistance)
            {
                ClosestDistance = CurrentHit.Distance;
                HitInfo = CurrentHit;

                Result = true;
            }
        }

        return Result;
    }
}
