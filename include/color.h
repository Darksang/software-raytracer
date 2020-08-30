#ifndef COLOR_H
#define COLOR_H

#include <iostream>

#include <glm/glm.hpp>

void WriteColor(std::ostream & Out, glm::vec3 Color, int SamplesPerPixel) {
    auto r = Color.x;
    auto g = Color.y;
    auto b = Color.z;

    // Divide the color by the number of samples
    auto Scale = 1.0 / SamplesPerPixel;
    r = sqrt(Scale * r);
    g = sqrt(Scale * g);
    b = sqrt(Scale * b);

    // Write the translated [0, 255] value of each color component
    Out << static_cast<int>(256 * Clamp(r, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * Clamp(g, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * Clamp(b, 0.0, 0.999)) << '\n';
}

#endif