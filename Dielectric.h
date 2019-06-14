#ifndef DIELECTRIC_H
#define DIELECTRIC_H

#include "Vec3.h"
#include "Material.h"

class Dielectric : public Material {

public:

    Dielectric(const float refIndex) : refIndex(refIndex) {}

    bool scatter(const Ray &rayIn, const HitRecord &rec, Vec3 &attenuation, Ray &scattered) const override {

        // Do not absorb any light.
        attenuation = Vec3(1);
        Vec3 outwardNormal;
        Vec3 reflected = reflect(rayIn.direction(), rec.normal);
        Vec3 refracted;
        float tmpRefIndex;
        float reflectProb;
        float cos = dot(rayIn.direction(), rec.normal) / rayIn.direction().length();
        if (dot(rayIn.direction(), rec.normal) > 0) {
            // Invert normal direction.
            outwardNormal = -rec.normal;
            tmpRefIndex = refIndex;
            cos = refIndex * cos;
        } else {
            outwardNormal = rec.normal;
            // Invert refraction index.
            tmpRefIndex = 1 / refIndex;
            cos = -cos;
        }
        // Refraction did take place.
        if (refract(rayIn.direction(), outwardNormal, tmpRefIndex, refracted)) {
            reflectProb = schlick(cos, refIndex);
        } else {
            reflectProb = 1;
        }

        if (drand48() < reflectProb) {
            scattered = Ray(rec.p, reflected);
        } else {
            scattered = Ray(rec.p, refracted);
        }
        return true;
    }

    float refIndex;
};

#endif
