#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>

// Usings

using std::shared_ptr;
using std::make_shared;

// Constants

const double Infinity = std::numeric_limits<double>::infinity();
const double Pi = 3.1415926535897932385;
constexpr double kEpsilon = 1e-8; 

// Utility Functions

inline double Deg2Rad(double Deg) {
    return Deg * Pi / 180.0;
}

inline double RandomDouble() {
    // Returns a random real in [0, 1)
    return rand() / (RAND_MAX + 1.0);
}

inline double RandomDouble(double Min, double Max) {
    return Min + (Max - Min) * RandomDouble();
}

inline double Clamp(double x, double Min, double Max)  {
    if (x < Min) return Min;
    if (x > Max) return Max;

    return x;
}

inline glm::vec3 Random() {
    return glm::vec3(RandomDouble(), RandomDouble(), RandomDouble());
}

inline glm::vec3 Random(double Min, double Max) {
    return glm::vec3(RandomDouble(Min, Max), RandomDouble(Min, Max), RandomDouble(Min, Max));
}

inline glm::vec3 RandomInUnitSphere() {
    while (true) {
        glm::vec3 p = Random(-1, 1);
        if (glm::length2(p) >= 1) 
            continue;

        return p;
    }
}

inline glm::vec3 RandomUnitVector() {
    auto a = RandomDouble(0, 2 * Pi);
    auto z = RandomDouble(-1, 1);
    auto r = sqrt(1 - z * z);

    return glm::vec3(r * cos(a), r * sin(a), z);
}

inline glm::vec3 Reflect(const glm::vec3& v, const glm::vec3& n) {
    return v - 2 * glm::dot(v, n) * n;
}

#endif