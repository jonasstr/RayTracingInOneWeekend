#include <iostream>
#include <fstream>
#include "Vec3.h"
#include "Ray.h"
#include "Hittable.h"
#include "Sphere.h"
#include "HittableList.h"

Vec3 color(const Ray r, Hittable *world) {

    HitRecord rec;
    if (world ->hit(r, 0.0, MAXFLOAT, rec)) {
        // Map normal values to RGB.
        return 0.5 * (rec.normal + 1);
    }
    // Between -1 and 1.
    Vec3 dir = normalize(r.direction());
    // 0 <= t <= 1.
    float t = 0.5 * (dir.y() + 1);
    // Interpolate between white and light blue.
    return (1 - t) * Vec3(1, 1, 1) + t * Vec3(0.2, 0.5, 1);
}

int main() {

    std::ofstream out("c5_two_spheres.ppm");
    // Save old output buffer.
    std::streambuf *coutbuf = std::cout.rdbuf();
    // Redirect std::cout to output file.
    std::cout.rdbuf(out.rdbuf());

    int nx = 200;
    int ny = 100;

    Vec3 origin(0, 0, 0);
    Vec3 lowerLeft(-2, -1, -1);
    Vec3 horizontal(4, 0, 0);
    Vec3 vertical(0, 2, 0);

    Hittable *list[2];
    list[0] = new Sphere(Vec3(0, 0, -1), 0.5);
    list[1] = new Sphere(Vec3(0, -100.5, -1), 100);
    Hittable *world = new HittableList(list, 2);

    std::cout << "P3\n" << nx << " " << ny << "\n255\n";
    for (int j = ny - 1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {

            float u = float(i) / float(nx);
            float v = float(j) / float(ny);
            Ray r(origin, lowerLeft + u * horizontal + v * vertical);
            Vec3 col = color(r, world);

            int ir = int(255.99 * col.r());
            int ig = int(255.99 * col.g());
            int ib = int(255.99 * col.b());
            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }
    // Reset to original output buffer.
    std::cout.rdbuf(coutbuf);
}