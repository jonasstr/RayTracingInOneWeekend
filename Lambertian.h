#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "Material.h"

class Lambertian : public Material {

public:

    explicit Lambertian(const Vec3 &albedo) : albedo(albedo) {}

    bool scatter(const Ray &rayIn, const HitRecord &rec, Vec3 &attenuation,
                 Ray &scattered) const override {
        // Randomize the direction of p by moving a random amount starting from the normal.
        Vec3 target = rec.p + rec.normal + randomPointInUnitSphere();
        // The new scattered ray.
        scattered = Ray(rec.p, target - rec.p);
        attenuation = albedo;
        return true;
    }

    Vec3 albedo;
};

#endif
