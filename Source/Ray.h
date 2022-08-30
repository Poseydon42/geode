#pragma once

#include <glm/glm.hpp>

namespace Geode
{
    struct Ray
    {
        glm::vec3 Origin;
        glm::vec3 Direction;
    };

    struct RayHit
    {
        float Distance;
        glm::vec3 Position;
        glm::vec3 Normal;
        size_t MaterialIndex;
    };
}
