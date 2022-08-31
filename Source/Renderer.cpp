#include "Renderer.h"

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "Camera.h"
#include "Material.h"
#include "Ray.h"
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

    void Render(const Film& Film, const Camera& Camera, const World& World)
    {
        static constexpr glm::vec3 BackgroundColor{0.0f, 0.0f, 0.0f};

        float AspectRatio = static_cast<float>(Film.Width) / static_cast<float>(Film.Height);
        float HalfViewportHeight = glm::tan(Camera.VerticalFOV / 2.0f);

        glm::vec3 Right = glm::normalize(glm::cross(Camera.Up, Camera.Direction));
        glm::vec3 Up = glm::cross(Camera.Direction, Right);

        // NOTE : these vectors are now non-normalized, but when we multiply them by pixel coordinates in [-1;1] space
        //        we will not have to additionally multiply them with aspect ratio and viewport height
        Right *= AspectRatio * HalfViewportHeight;
        Up *= HalfViewportHeight;

        auto* Pixel = static_cast<uint32_t*>(Film.Memory);
        for (uint16_t Y = 0; Y < Film.Height; Y++)
        {
            for (uint16_t X = 0; X < Film.Width; X++)
            {
                // Transforming X and Y into [-1;1] range
                // NOTE: flipping sign of the Y coordinate because the world Y coordinate is from the bottom to the top,
                // but the pixel order in the image is top to bottom
                float RealX = (static_cast<float>(X) + 0.5f) / static_cast<float>(Film.Width) * 2.0f - 1.0f;
                float RealY = -((static_cast<float>(Y) + 0.5f) / static_cast<float>(Film.Height) * 2.0f - 1.0f);

                glm::vec3 PixelColor = BackgroundColor;

                glm::vec3 PixelPosition = Camera.Position + Camera.Direction + RealX * Right + RealY * Up;

                Ray Ray = {};
                Ray.Origin = Camera.Position;
                Ray.Direction = glm::normalize(PixelPosition - Camera.Position);

                RayHit PossibleHit = {};
                if (TryIntersect(World, Ray, PossibleHit))
                {
                    PixelColor = World.Materials[PossibleHit.MaterialIndex].Color;
                }

                *Pixel++ = ComposeColor(PixelColor);
            }
        }
    }
}