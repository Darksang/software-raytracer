#ifndef RAY_H
#define RAY_H

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/scalar_multiplication.hpp>

class Ray {
    public:
        Ray() {}
        Ray(const glm::vec3 & Origin, const glm::vec3 & Direction)
            : Origin(Origin), Direction(Direction)
        {}

        glm::vec3 At(double t) const {
            return Origin + t * Direction;
        }

        glm::vec3 Origin;
        glm::vec3 Direction;
};

#endif