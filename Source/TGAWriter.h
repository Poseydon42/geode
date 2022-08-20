#pragma once

#include <cstdint>
#include <string>

namespace Geode
{
    /*
     * Stores a given image in a TGA file under given name
     * Image must be BGRA 4 bytes per pixel
     */
    bool WriteTGA(const std::string& Name, uint16_t Width, uint16_t Height, const void* Data);
} // namespace Geode