#pragma once

#include <glm/glm.hpp>

namespace Geode
{
    struct Film
    {
        uint32_t Width;
        uint32_t Height;
        uint32_t SamplesPerPixel;
        void* Memory;
    };
}
