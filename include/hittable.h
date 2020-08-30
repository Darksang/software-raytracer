#ifndef HITTABLE_H
#define HITTABLE_H

#include <glm/glm.hpp>

#include "raytracer.h"
#include "ray.h"

class Material;

struct HitRecord {
    glm::vec3 Point;
    glm::vec3 Normal;
    shared_ptr<Material> MaterialPtr;
    double t;
    double u;
    double v;
    bool FrontFace;

    inline void SetFaceNormal(const Ray & r, const glm::vec3 & OutwardNormal) {
        FrontFace = glm::dot(r.Direction, OutwardNormal) < 0;
        Normal = FrontFace ? OutwardNormal : -OutwardNormal;
    }
};

class Hittable {
    public:
        virtual bool Hit(const Ray & r, double t_min, double t_max, HitRecord & Rec) const = 0;
};

#endif