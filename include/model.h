#ifndef MODEL_H
#define MODEL_H

#include <glm/glm.hpp>

#include "mesh.h"
#include "hittable.h"
#include "triangle.h"

class Model : public Hittable {
    public:
        Model(Mesh * Mesh, shared_ptr<Material> m);

        virtual bool Hit(const Ray & r, double t_min, double t_max, HitRecord & Rec) const override;

    private:
        std::vector<Triangle> Triangles;
        shared_ptr<Material> MaterialPtr;
};

#endif