#ifndef CAMERA_H
#define CAMERA_H

#include "Vec3.h"
#include "Ray.h"

class Camera {

public:

    Camera() {
        origin = Vec3(0, 0, 0);
        lowerLeft = Vec3(-2, -1, -1);
        horizontal = Vec3(4, 0, 0);
        vertical = Vec3(0, 2, 0);
    }

    Ray getRay(float u, float v) {
        return {origin, lowerLeft + u * horizontal + v * vertical - origin};
    }

    Vec3 origin;
    Vec3 lowerLeft;
    Vec3 horizontal;
    Vec3 vertical;
};

#endif
