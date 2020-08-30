#ifndef VERTEX_H
#define VERTEX_H

#include <glm/glm.hpp>

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;

    bool operator==(const Vertex & Other) const {
        return Position == Other.Position && Normal == Other.Normal && TexCoords == Other.TexCoords;
    }
};

#endif