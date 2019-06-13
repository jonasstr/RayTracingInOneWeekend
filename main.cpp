#include <iostream>
#include <fstream>
#include "vec3.h"
#include "ray.h"

float hitSphere(const vec3 &center, float radius, const ray &r) {
    vec3 oc = r.origin() - center;
    float a = dot(r.direction(), r.direction());
    float b = 2 * dot(r.direction(), oc);
    float c = dot(oc, oc) - radius * radius;
    float discriminant = b * b - 4 * a * c;
    // Solution to the quadratic formula is not real.
    if (discriminant < 0) {
        return -1;
    }
    else {
        // Return the solution for (-b - sqrt(b²-4ac)) / 2a.
        return (-b - sqrt(discriminant)) / (2*a);
    }
}

vec3 color(ray r) {

    vec3 sphereCenter = vec3(0, 0, -1);
    float t = hitSphere(sphereCenter, 0.5, r);
    if (t > 0) {
        // Compute normal from hit position.
        vec3 normal = normalize(r.point_at_parameter(t) - sphereCenter);
        // Map normal values to RGB.
        return 0.5 * (normal + 1);
    }

    // Between -1 and 1.
    vec3 dir = normalize(r.direction());
    // 0 <= t <= 1.
    t = 0.5 * (dir.y() + 1);
    // Interpolate between white and light blue.
    return (1 - t) * vec3(1, 1, 1) + t * vec3(0.2, 0.5, 1);
}

int main() {
    int nx = 200;
    int ny = 100;

    vec3 origin(0, 0, 0);
    vec3 lowerLeft(-2, -1, -1);
    vec3 horizontal(4, 0, 0);
    vec3 vertical(0, 2, 0);

    std::ofstream out("circle_normals.ppm");
    // Save old output buffer.
    std::streambuf *coutbuf = std::cout.rdbuf();
    // Redirect std::cout to output file.
    std::cout.rdbuf(out.rdbuf());

    std::cout << "P3\n" << nx << " " << ny << "\n255\n";
    for (int j = ny - 1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {

            float u = float(i) / float(nx);
            float v = float(j) / float(ny);
            ray r(origin, lowerLeft + u * horizontal + v * vertical);
            vec3 col = color(r);

            int ir = int(255.99 * col.r());
            int ig = int(255.99 * col.g());
            int ib = int(255.99 * col.b());
            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }
    // Reset to original output buffer.
    std::cout.rdbuf(coutbuf);
}