#ifndef CAMERA_H
#define CAMERA_H

#include "Vec3.h"
#include "Ray.h"

class Camera {

public:

    Camera(const Vec3 &lookFrom, const Vec3 &lookAt, const Vec3 &up, const float vFOV, const float aspectRatio,
           const float aperture, const float focusDist) {

        lensRadius = aperture / 2;

        // Convert to radians.
        const float theta = vFOV * M_PI / 180;
        const float halfHeight = tan(theta / 2);
        const float halfWidth = aspectRatio * halfHeight;

        w = normalize(lookFrom - lookAt);
        u = normalize(cross(up, w));
        v = cross(w, u);

        origin = lookFrom;
        lowerLeft = origin - halfWidth * focusDist * u - halfHeight * focusDist * v - focusDist * w;
        horizontal = 2 * halfWidth * focusDist * u;
        vertical = 2 * halfHeight * focusDist * v;
    }

    Ray getRay(float s, float t) {
        const Vec3 randomStart = lensRadius * randomPointInUnitDisk();
        const Vec3 offset = u * randomStart.x() + v * randomStart.y();
        return {origin + offset, lowerLeft + s * horizontal + t * vertical - origin - offset};
    }

    float lensRadius;

    Vec3 u, v, w;
    Vec3 origin;
    Vec3 lowerLeft;
    Vec3 horizontal;
    Vec3 vertical;

private:

    Vec3 randomPointInUnitDisk() const {
        Vec3 p;
        do {
            p = 2.0 * Vec3(drand48(), drand48(), 0) - Vec3(1, 1, 0);
        } while (dot(p, p) >= 1.0);
        return p;
    }
};

#endif
