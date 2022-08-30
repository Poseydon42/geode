#include <chrono>
#include <cstring>
#include <glm/glm.hpp>
#include <iostream>

#include "Material.h"
#include "Ray.h"
#include "Surface.h"
#include "TGAWriter.h"
#include "World.h"

namespace Geode
{
    static uint32_t ComposeColor(const glm::vec3 Color)
    {
        auto R = static_cast<uint32_t>(Color.r * 255.5f);
        auto G = static_cast<uint32_t>(Color.g * 255.5f);
        auto B = static_cast<uint32_t>(Color.b * 255.5f);
        uint32_t A = 0xFF;

        // The byte order in memory is BGRA, but since x86_64 is little-endian system we need to invert the order
        // when composing the numeric pixel representation
        uint32_t Result = (A << 24) | (R << 16) | (G << 8) | (B << 0);

        return Result;
    }

    int DeferredMain(int, char**)
    {
        constexpr uint16_t Width = 1024;
        constexpr uint16_t Height = 1024;
        constexpr size_t BytesPerPixel = 4;

        Material Material1 = {{0.5f, 0.7f, 1.0f}};
        Material Material2 = {{0.5f, 0.0f, 1.0f}};
        Sphere Sphere1 = {{0.0f, 1.0f, -5.0f}, 1.0f, 0};
        Sphere Sphere2 = {{2.0f, 1.5f, -5.0f}, 1.0f, 1};

        World World = {{Material1, Material2}, {Sphere1, Sphere2}};

        auto* Image = malloc(Width * Height * BytesPerPixel);

        auto StartTimePoint = std::chrono::high_resolution_clock::now();

        // We assume that camera is located at (0;0;0) and facing the -Z direction
        // The coordinate system is right-handed, with X pointing to the right, Y upwards and Z from the screen to the
        // viewer
        // The image plane is located at Z = -1.0 and is parallel to the XY plane
        static constexpr float ImagePlaneZ = -1.0f;
        glm::vec3 BackgroundColor{0.0f, 0.0f, 0.0f};
        auto* Pixel = static_cast<uint32_t*>(Image);
        for (uint16_t Y = 0; Y < Height; Y++)
        {
            for (uint16_t X = 0; X < Width; X++)
            {
                // Transforming X and Y into [-1;1] range
                // NOTE: flipping sign of the Y coordinate because the world Y coordinate is from the bottom to the top,
                // but the pixel order in the image is top to bottom
                float RealX = (static_cast<float>(X) + 0.5f) / static_cast<float>(Width) * 2.0f - 1.0f;
                float RealY = -((static_cast<float>(Y) + 0.5f) / static_cast<float>(Height) * 2.0f - 1.0f);

                glm::vec3 PixelColor = BackgroundColor;

                Ray Ray = {};
                Ray.Origin = glm::vec3(0.0f);
                Ray.Direction = glm::normalize(glm::vec3(RealX, RealY, ImagePlaneZ));

                RayHit PossibleHit = {};
                if (TryIntersect(World, Ray, PossibleHit))
                {
                    PixelColor = World.Materials[PossibleHit.MaterialIndex].Color;
                }

                *Pixel++ = ComposeColor(PixelColor);
            }
        }

        auto EndTimePoint = std::chrono::high_resolution_clock::now();
        auto Duration = EndTimePoint - StartTimePoint;

        std::cout << "Rendering finished in " << duration_cast<std::chrono::milliseconds>(Duration).count() << " ms"
                  << std::endl;

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
