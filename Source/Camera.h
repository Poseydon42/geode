#pragma once

#include <glm/glm.hpp>

namespace Geode
{
    struct Film
    {
        uint32_t Width;
        uint32_t Height;
        uint32_t SamplesPerPixelSide;
        void* Memory;
    };

    struct Camera
    {
        glm::vec3 Position;
        glm::vec3 Direction;
        glm::vec3 Up;
        float VerticalFOV; // In radians
    };
}
