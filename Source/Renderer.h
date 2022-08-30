#pragma once

#include <cstdint>

namespace Geode
{
    struct Film;
    struct World;

    void Render(const Film& Film, const World& World);
}