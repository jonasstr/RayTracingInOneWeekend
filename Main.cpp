#include <iostream>
#include <fstream>
#include "Vec3.h"
#include "Ray.h"
#include "Hittable.h"
#include "Sphere.h"
#include "HittableList.h"
#include "Camera.h"

Vec3 randomPointInUnitSphere() {
    Vec3 p;
    do {
        // Choose a random point.
        p = 2 * Vec3(drand48()) - Vec3(1);
        // Check whether the point is within the unit sphere.
    } while (p.squared_length() >= 1.0);
    return p;
}

Vec3 color(const Ray r, Hittable *world) {

    HitRecord rec;
    if (world->hit(r, 0.001, MAXFLOAT, rec)) {
        // Randomize the direction of p by moving a random amount starting from the normal.
        Vec3 target = rec.p + rec.normal + randomPointInUnitSphere();
        // Reflect again recursively starting from the new point.
        return 0.5 * color(Ray(rec.p, target - rec.p), world);
    } else {
        // Between -1 and 1.
        Vec3 dir = normalize(r.direction());
        // 0 <= t <= 1.
        float t = 0.5 * (dir.y() + 1);
        // Interpolate between white and light blue.
        return (1 - t) * Vec3(1, 1, 1) + t * Vec3(0.2, 0.5, 1);
    }
}

int main() {

    std::ofstream out("c6_diffuse_material.ppm");
    // Save old output buffer.
    std::streambuf *coutbuf = std::cout.rdbuf();
    // Redirect std::cout to output file.
    std::cout.rdbuf(out.rdbuf());

    int nx = 200;
    int ny = 100;
    int ns = 100;

    Hittable *list[2];
    list[0] = new Sphere(Vec3(0, 0, -1), 0.5);
    list[1] = new Sphere(Vec3(0, -100.5, -1), 100);
    Hittable *world = new HittableList(list, 2);

    Camera cam;

    std::cout << "P3\n" << nx << " " << ny << "\n255\n";
    for (int j = ny - 1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {

            Vec3 col(0, 0, 0);
            // Create ns random rays through each pixel and average their colors.
            for (int s = 0; s < ns; s++) {
                float u = float(i + drand48()) / float(nx);
                float v = float(j + drand48()) / float(ny);
                Ray r = cam.getRay(u, v);
                Vec3 p = r.pointAtParameter(2.0);
                col += color(r, world);
            }
            col /= float(ns);
            // Apply gamma correction.
            col = Vec3(sqrt(col.r()), sqrt(col.g()), sqrt(col.b()));

            int ir = int(255.99 * col.r());
            int ig = int(255.99 * col.g());
            int ib = int(255.99 * col.b());
            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }
    // Reset to original output buffer.
    std::cout.rdbuf(coutbuf);
}