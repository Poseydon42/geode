#include <chrono>
#include <cstring>
#include <glm/glm.hpp>
#include <iostream>

#include "Camera.h"
#include "Material.h"
#include "Ray.h"
#include "Renderer.h"
#include "Surface.h"
#include "TGAWriter.h"
#include "World.h"

namespace Geode
{
    int DeferredMain(int, char**)
    {
        constexpr uint16_t Width = 1024;
        constexpr uint16_t Height = 1024;
        constexpr size_t BytesPerPixel = 4;

        Material Material1 = {{0.5f, 0.7f, 1.0f}};
        Material Material2 = {{0.5f, 0.0f, 1.0f}};
        Sphere Sphere1 = {{0.0f, 1.0f, -5.0f}, 1.0f, 0};
        Sphere Sphere2 = {{3.0f, -3.5f, -5.0f}, 1.0f, 1};

        World World = {{Material1, Material2}, {Sphere1, Sphere2}};

        auto* Image = malloc(Width * Height * BytesPerPixel);

        Film Target = { Width, Height, 1, Image };

        auto StartTimePoint = std::chrono::high_resolution_clock::now();

        Render(Target, World);

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
