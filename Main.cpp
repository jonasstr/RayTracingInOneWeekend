#include <iostream>
#include <fstream>

#include "Vec3.h"
#include "Ray.h"
#include "Hittable.h"
#include "Material.h"
#include "Sphere.h"
#include "HittableList.h"
#include "Camera.h"
#include "Lambertian.h"
#include "Metal.h"

Vec3 color(const Ray r, Hittable *world, int depth, const int maxDepth) {

    HitRecord rec;
    if (world->hit(r, 0.001, MAXFLOAT, rec)) {
        Ray scattered;
        Vec3 attenuation;
        if (depth < maxDepth && rec.matPtr->scatter(r, rec, attenuation, scattered)) {
            return attenuation*color(scattered, world, depth+1, maxDepth);
        } else {
            // Black if max depth has been exceeded.
            return {0, 0, 0};
        }
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

    std::ofstream out("c8_metal_and_lambertian_fuzzy.ppm");
    // Save old output buffer.
    std::streambuf *coutbuf = std::cout.rdbuf();
    // Redirect std::cout to output file.
    std::cout.rdbuf(out.rdbuf());

    int nx = 200;
    int ny = 100;
    int ns = 100;

    Hittable *list[4];
    list[0] = new Sphere(Vec3(0, 0, -1), 0.5, new Lambertian(Vec3(0.8, 0.3, 0.3)));
    list[1] = new Sphere(Vec3(0, -100.5, -1), 100, new Lambertian(Vec3(0.8, 0.8, 0.0)));
    list[2] = new Sphere(Vec3(1, 0, -1), 0.5, new Metal(Vec3(0.8, 0.6, 0.2), 0.1));
    list[3] = new Sphere(Vec3(-1, 0, -1), 0.5, new Metal(Vec3(0.8, 0.8, 0.8), 1.0));
    Hittable *world = new HittableList(list, 4);

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
                col += color(r, world, 0, 50);
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