#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "vertex.h"
#include "hittable.h"

class Triangle : public Hittable {
    public:
        Triangle(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c, shared_ptr<Material> m);
        Triangle(const Vertex& v0, const Vertex& v1, const Vertex& v2, shared_ptr<Material> m);

        virtual bool Hit(const Ray & r, double t_min, double t_max, HitRecord & Rec) const override;

    private:
        glm::vec3 a;
        glm::vec3 b;
        glm::vec3 c;

        glm::vec3 EdgeV0V1;
        glm::vec3 EdgeV0V2;

        shared_ptr<Material> MaterialPtr;
};

#endif