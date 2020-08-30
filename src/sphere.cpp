#include "sphere.h"

#include <glm/gtx/norm.hpp>

Sphere::Sphere() {
    Center = glm::vec3(0, 0, -1);
    Radius = 0.5;
}

Sphere::Sphere(glm::vec3 Center, double r, shared_ptr<Material> m) : Center(Center), Radius(r), MaterialPtr(m) { }

bool Sphere::Hit(const Ray & r, double t_min, double t_max, HitRecord & Rec) const {
    glm::vec3 oc = r.Origin - Center;
    auto a = glm::length2(r.Direction);
    auto half_b = glm::dot(oc, r.Direction);
    auto c = glm::length2(oc) - Radius * Radius;
    auto discriminant = half_b * half_b - a * c;

    if (discriminant > 0) {
        auto root = sqrt(discriminant);

        auto temp = (-half_b - root) / a;

        if (temp < t_max && temp > t_min) {
            Rec.t = temp;
            Rec.Point = r.At(Rec.t);
            glm::vec3 OutwardNormal = (Rec.Point - Center) / Radius;
            Rec.SetFaceNormal(r, OutwardNormal);
            Rec.MaterialPtr = MaterialPtr;
            return true;
        }

        temp = (-half_b + root) / a;
        if (temp < t_max && temp > t_min) {
            Rec.t = temp;
            Rec.Point = r.At(Rec.t);
            glm::vec3 OutwardNormal = (Rec.Point - Center) / Radius;
            Rec.SetFaceNormal(r, OutwardNormal);
            Rec.MaterialPtr = MaterialPtr;
            return true;
        }
    }

    return false;
}