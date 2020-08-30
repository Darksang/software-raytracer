#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm/glm.hpp>

#include "ray.h"
#include "raytracer.h"
#include "hittable.h"

class Material {
    public:
        virtual bool Scatter(const Ray& r, const HitRecord& Rec, glm::vec3& Attenuation, Ray& Scattered) const = 0;
};

class Lambertian : public Material {
    public:
        Lambertian(const glm::vec3& Albedo) : Albedo(Albedo) { }

        virtual bool Scatter(const Ray& r, const HitRecord& Rec, glm::vec3& Attenuation, Ray& Scattered) const override {
            glm::vec3 ScatterDirection = Rec.Normal + RandomUnitVector();
            Scattered = Ray(Rec.Point, ScatterDirection);
            Attenuation = Albedo;
            return true;
        }

    private:
        glm::vec3 Albedo;
};

class Metal : public Material {
    public:
        Metal(const glm::vec3& Albedo, double Fuzz) : Albedo(Albedo), Fuzz(Fuzz < 1 ? Fuzz : 1) { }

        virtual bool Scatter(const Ray& r, const HitRecord& Rec, glm::vec3& Attenuation, Ray& Scattered) const override {
            glm::vec3 Reflected = Reflect(glm::normalize(r.Direction), Rec.Normal);
            Scattered = Ray(Rec.Point, Reflected + Fuzz * RandomInUnitSphere());
            Attenuation = Albedo;
            return (glm::dot(Scattered.Direction, Rec.Normal) > 0);
        }

    private:
        glm::vec3 Albedo;
        double Fuzz;
};

#endif