#pragma once

#include <cstdint>

namespace Geode
{
    struct Camera;
    struct Film;
    struct World;

    void Render(const Film& Film, const Camera& Camera, const World& World);
}