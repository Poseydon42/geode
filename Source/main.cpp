#include <cstring>
#include <iostream>

#include "TGAWriter.h"

namespace Geode
{
    int DeferredMain(int, char**)
    {
        constexpr uint16_t Width = 1024;
        constexpr uint16_t Height = 1024;
        constexpr size_t BytesPerPixel = 4;

        auto* Image = malloc(Width * Height * BytesPerPixel);

        auto* Pixel = static_cast<uint8_t*>(Image);
        for (uint16_t Y = 0; Y < Height; Y++)
        {
            for (uint16_t X = 0; X < Height; X++)
            {
                *Pixel++ = 0;       // Blue
                *Pixel++ = Y % 255; // Green
                *Pixel++ = X % 255; // Red
                *Pixel++ = 0xFF;    // Alpha
            }
        }

        if (!WriteTGA("result.tga", Width, Height, Image))
        {
            std::cerr << "Failed to write the result image file" << std::endl;
            return -1;
        }

        std::cout << "Done" << std::endl;
        return 0;
    }
} // namespace Geode

int main(int ArgCount, char** ArgValues)
{
    return Geode::DeferredMain(ArgCount, ArgValues);
}
