#ifndef SPHERE_H
#define SPHERE_H

#include <glm/glm.hpp>

#include "hittable.h"

class Sphere : public Hittable {
    public:
        Sphere();
        Sphere(glm::vec3 Center, double r, shared_ptr<Material> m);

        virtual bool Hit(const Ray & r, double t_min, double t_max, HitRecord & Rec) const override;

    private:
        glm::vec3 Center;
        double Radius;
        shared_ptr<Material> MaterialPtr;
};

#endif