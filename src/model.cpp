#include "model.h"

Model::Model(Mesh * Mesh, shared_ptr<Material> m) : MaterialPtr(m) {
    int32_t TotalTriangles = Mesh->IndexBuffer.size() / 3;

    for (int32_t i = 0; i < TotalTriangles; i++) {
        glm::vec3 v0 = Mesh->VertexBuffer[Mesh->IndexBuffer[i * 3]].Position;
        glm::vec3 v1 = Mesh->VertexBuffer[Mesh->IndexBuffer[i * 3 + 1]].Position;
        glm::vec3 v2 = Mesh->VertexBuffer[Mesh->IndexBuffer[i * 3 + 2]].Position;

        Triangles.push_back(Triangle(v0, v1, v2, m));
    }
}

bool Model::Hit(const Ray & r, double t_min, double t_max, HitRecord & Rec) const {
    glm::vec3 Normal(0, 0, 0);

    double t = Infinity;
    bool Hit = false;

    for (Triangle T : Triangles) {
        if (T.Hit(r, t_min, t_max, Rec)) {
            if (Rec.t < t) {
                t = Rec.t;
                Normal = Rec.Normal;
            }

            Hit = true;
        }
    }

    Rec.t = t;
    Rec.Normal = Normal;
    Rec.Point = r.At(Rec.t);

    return Hit;
}