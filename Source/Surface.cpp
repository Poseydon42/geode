#include "Surface.h"

#include "Ray.h"

namespace Geode
{
    bool TryIntersect(const Sphere& Sphere, const Ray& Ray, RayHit& HitInfo)
    {
        // Solving the equation of line to sphere intersection
        // A - origin of the line
        // B - direction of the line
        // C - center of the sphere
        // R - radius of the sphere
        // Solving for t (distance along the line from the origin towards the direction)
        // The equation is:
        // t^2*B*B + 2tB*(A-C) + (A-C)*(A-C) - R^2 = 0
        // Solutions of the quadratic equation:
        // x = (-b +- sqrt(D)) / 2a

        // Quadratic coefficients:
        float A = glm::dot(Ray.Direction, Ray.Direction);
        float B = 2.0f * glm::dot(Ray.Origin - Sphere.Position, Ray.Direction);
        float C = glm::dot(Ray.Origin - Sphere.Position, Ray.Origin - Sphere.Position) - Sphere.Radius * Sphere.Radius;

        float Discriminant = B * B - 4 * A * C;
        if (Discriminant < 0.0f)
        {
            // No solutions if the discriminant is less than zero
            return false;
        }

        float T1 = (-B - glm::sqrt(Discriminant)) / (2.0f * A);
        float T2 = (-B + glm::sqrt(Discriminant)) / (2.0f * A);

        // T1 is always less than T2, so we try to use it (because we want the closest point of intersection)
        float T = T1;
        if (T < 0.0f) // But if T1 is "behind" the ray then we try T2
            T = T2;
        if (T < 0.0f) // If T2 is behind the ray as well then report that the ray does not intersect the sphere
            return false;

        HitInfo.Distance = T;
        HitInfo.Position = Ray.Origin + Ray.Direction * T;
        HitInfo.Normal = glm::normalize(HitInfo.Position - Sphere.Position);
        HitInfo.MaterialIndex = Sphere.MaterialIndex;

        return true;
    }
} // namespace Geode
