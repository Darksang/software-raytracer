#ifndef MESH_H
#define MESH_H

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/hash.hpp>

#include <vector>
#include <string>

#include "vertex.h"

// https://en.cppreference.com/w/cpp/utility/hash
namespace std {
    template<> struct hash<Vertex> {
        size_t operator()(Vertex const & Vertex) const {
            return ((hash<glm::vec3>()(Vertex.Position) ^
                    (hash<glm::vec3>()(Vertex.Normal) << 1)) >> 1) ^
                    (hash<glm::vec2>()(Vertex.TexCoords) << 1);
        }
    };
}

class Mesh {
    public:
        Mesh();
        ~Mesh();

        void LoadOBJ(const std::string & File);
        void LoadTexture(const std::string & File);

        std::vector<Vertex> VertexBuffer;
        std::vector<uint32_t> IndexBuffer;
        //Texture * MeshTexture;
};

#endif