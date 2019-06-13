#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray {

public:
    ray(vec3 a, vec3 b) {
        A = a;
        B = b;
    };

    inline vec3 origin() const { return A; }

    inline vec3 direction() const { return B; }

    vec3 point_at_parameter(float t) { return A + t * B; }

    vec3 A;
    vec3 B;
};

#endif
