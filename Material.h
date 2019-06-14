#ifndef MATERIAL_H
#define MATERIAL_H

#include "Ray.h"
#include "Hittable.h"

class Material {

public:

    virtual bool scatter(const Ray &rayIn, const HitRecord &rec,
                         Vec3 &attenuation, Ray &scattered) const = 0;

protected:
    Vec3 randomPointInUnitSphere() const {
        Vec3 p;
        do {
            // Choose a random point.
            p = 2 * Vec3(drand48()) - Vec3(1);
            // Check whether the point is within the unit sphere.
        } while (p.squared_length() >= 1.0);
        return p;
    }

    Vec3 reflect(const Vec3 &incident, const Vec3 &normal) const {
        return incident - 2 * dot(incident, normal) * normal;
    }

    bool refract(const Vec3 &incident, const Vec3 &normal, float refIndex, Vec3 &refracted) const {

        const Vec3 normalized = normalize(incident);
        const float cosI = dot(normalized, normal);
        float discriminant = 1.0 - refIndex * refIndex * (1.0 - cosI * cosI);
        // Check if the root has a real solution.
        if (discriminant > 0) {
            refracted = refIndex * (normalized - normal * cosI) - normal * sqrt(discriminant);
            return true;
        }
        return false;

        /*const float cosI = -dot(incident, normal);
        const double sinT2 = 1 - refIndex * refIndex * (1 - cosI * cosI);
        // Check if the root has a real solution.
        if (sinT2 > 0) {
            refracted = refIndex * incident + (refIndex * cosI - sqrt(1 - sinT2)) * refIndex;
            return true;
        } else {
            return false;
        }*/
    }

    float schlick(float cos, float refIndex) const {
        float r0 = (1 -refIndex) / (1 + refIndex);
        r0 *= r0;
        return r0 + (1- r0) * pow((1 - cos), 5);
    }
};

#endif
