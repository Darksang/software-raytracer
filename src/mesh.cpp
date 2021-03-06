#include "mesh.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

#include <unordered_map>
#include <iostream>

Mesh::Mesh() {
    //MeshTexture = nullptr;
}

Mesh::~Mesh() {
    VertexBuffer.clear();
    IndexBuffer.clear();

    //delete MeshTexture;
}

void Mesh::LoadOBJ(const std::string & File) {
    std::unordered_map<Vertex, uint32_t> UniqueVertices;

    tinyobj::attrib_t Attributes;
    std::vector<tinyobj::shape_t> Shapes;
    std::vector<tinyobj::material_t> Materials;
    std::string Warning, Error;

    if (tinyobj::LoadObj(&Attributes, &Shapes, &Materials, &Warning, &Error, File.c_str())) {
        /*std::cerr << "Number of Vertices = " << (int)(Attributes.vertices.size() / 3) << std::endl;
        std::cerr << "Number of Normals = " << (int)(Attributes.normals.size() / 3) << std::endl;
        std::cerr << "Number of TexCoords = " << (int)(Attributes.texcoords.size() / 2) << std::endl;
        std::cerr << "Number of Shapes = " << Shapes.size() << std::endl; */

        for (const auto & Shape : Shapes) {
            for (const auto & Index : Shape.mesh.indices) {
                Vertex V{};

                V.Position = {
                    Attributes.vertices[3 * Index.vertex_index],
                    Attributes.vertices[3 * Index.vertex_index + 1],
                    Attributes.vertices[3 * Index.vertex_index + 2]
                };

                V.Normal = {
                    Attributes.normals[3 * Index.normal_index],
                    Attributes.normals[3 * Index.normal_index + 1],
                    Attributes.normals[3 * Index.normal_index + 2],
                };

                V.TexCoords = {
                    Attributes.texcoords[2 * Index.texcoord_index],
                    Attributes.texcoords[2 * Index.texcoord_index + 1]
                };

                // If this vertex isn't duplicate, add it
                if (UniqueVertices.count(V) == 0) {
                    UniqueVertices[V] = static_cast<uint32_t>(VertexBuffer.size());
                    VertexBuffer.push_back(V); 
                }

                IndexBuffer.push_back(UniqueVertices[V]);
            }
        }

        std::cerr << "\n#### OBJ Mesh: " << File << " ####" << std::endl;
        std::cerr << "Vertices = " << VertexBuffer.size() << std::endl;
        std::cerr << "Indices = " << IndexBuffer.size() << std::endl;
        std::cerr << "Triangles = " << IndexBuffer.size() / 3 << std::endl;
        std::cerr << "####" << std::endl;
    }
}