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
};

#endif
