#ifndef RAY_H
#define RAY_H

#include "Vec3.h"

class Ray {

public:

    Ray() {}

    Ray(Vec3 a, Vec3 b) {
        A = a;
        B = b;
    };

    inline Vec3 origin() const { return A; }

    inline Vec3 direction() const { return B; }

    Vec3 pointAtParameter(float t) const { return A + t * B; }

    Vec3 A;
    Vec3 B;
};

#endif
