#ifndef SPHERE_H
#define SPHERE_H

#include "Hittable.h"
#include <memory>

class Sphere : public Hittable {

public:

    Sphere(Vec3 center, float r, Material* material)
            : center(center), radius(r), material(material) {};

    Vec3 center;
    float radius;
    std::unique_ptr<Material> material;

    bool hit(const Ray &r, float tMin, float tMax, HitRecord &rec) const {

        Vec3 oc = r.origin() - center;
        float a = dot(r.direction(), r.direction());
        float b = dot(r.direction(), oc);
        float c = dot(oc, oc) - radius * radius;
        float discriminant = b * b - a * c;
        // Quadratic formula has a real solution.
        if (discriminant > 0) {
            const float tmp1 = (-b - sqrt(b * b - a * c)) / a;
            if (tMin < tmp1 && tmp1 < tMax) {
                rec.t = tmp1;
                rec.p = r.pointAtParameter(rec.t);
                rec.normal = (rec.p - center) / radius;
                rec.matPtr = material.get();
                return true;
            }
            const float tmp2 = (-b + sqrt(b * b - a * c)) / a;
            if (tMin < tmp2 && tmp2 < tMax) {
                rec.t = tmp2;
                rec.p = r.pointAtParameter(rec.t);
                rec.normal = (rec.p - center) / radius;
                rec.matPtr = material.get();
                return true;
            }
        }
        return false;
    }
};

#endif
