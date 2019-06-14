cmake_minimum_required(VERSION 3.13)
project(RTInAWeekend)

set(CMAKE_CXX_STANDARD 14)

add_executable(RTInAWeekend Main.cpp Vec3.h Ray.h Hittable.h Sphere.h HittableList.h Camera.h Lambertian.h Material.h Metal.h)