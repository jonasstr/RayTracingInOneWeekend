#ifndef METAL_H
#define METAL_H

#include "Material.h"

class Metal : public Material {

public:

    explicit Metal(const Vec3 &albedo, const float f) : albedo(albedo) {
        fuzziness = fmin(f, 1);
    }

    bool scatter(const Ray &rayIn, const HitRecord &rec, Vec3 &attenuation,
                 Ray &scattered) const override {

        Vec3 reflected = reflect(rayIn.direction(), rec.normal);
        // Add small random change in direction controlled by fuzziness.
        scattered = Ray(rec.p, reflected + fuzziness * randomPointInUnitSphere());
        attenuation = albedo;
        // Test whether the reflected ray points in the direction of the normal,
        // i.e. is not reflected inwards.
        return dot(scattered.direction(), rec.normal) > 0;
    }

    Vec3 reflect(const Vec3 &v, const Vec3 &n) const {
        return v - 2 * dot(v, n) * n;
    }

    Vec3 albedo;
    float fuzziness;
};

#endif
