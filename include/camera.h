#ifndef CAMERA_H
#define CAMERA_H

#include "ray.h"
#include "raytracer.h"

class Camera {
    public:
        Camera(glm::vec3 LookFrom, glm::vec3 LookAt, glm::vec3 Up, double FoV, double AspectRatio) {
            auto Theta = Deg2Rad(FoV);
            auto h = tan(Theta / 2);
            auto ViewportHeight = 2.0 * h;
            auto ViewportWidth = AspectRatio * ViewportHeight;

            auto w = glm::normalize(LookFrom - LookAt);
            auto u = glm::normalize(glm::cross(Up, w));
            auto v = glm::cross(w, u);

            Origin = LookFrom;
            Horizontal = ViewportWidth * u;
            Vertical = ViewportHeight * v;
            LowerLeftCorner = Origin - Horizontal / 2 - Vertical / 2 - w;
        }

        Ray GetRay(double s, double t) const {
            return Ray(Origin, LowerLeftCorner + s * Horizontal + t * Vertical - Origin);
        }

    private:
        glm::vec3 Origin;
        glm::vec3 LowerLeftCorner;
        glm::vec3 Horizontal;
        glm::vec3 Vertical;
};

#endif