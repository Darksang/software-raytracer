#include "triangle.h"

Triangle::Triangle(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c, shared_ptr<Material> m) : a(a), b(b), c(c), MaterialPtr(m) {
    EdgeV0V1 = b - a;
    EdgeV0V2 = c - a;
}
Triangle::Triangle(const Vertex& v0, const Vertex& v1, const Vertex& v2, shared_ptr<Material> m) {
    // TODO: With vertex
    EdgeV0V1 = v1.Position - v0.Position;
    EdgeV0V2 = v2.Position - v0.Position;
}

// http://www.graphics.cornell.edu/pubs/1997/MT97.html
bool Triangle::Hit(const Ray & r, double t_min, double t_max, HitRecord & Rec) const {
    glm::vec3 pVec = glm::cross(r.Direction, EdgeV0V2);
    double Det = glm::dot(pVec, EdgeV0V1);

    // Culling
    if (Det < kEpsilon)
        return false;

    double InvDet = 1.0 / Det;

    glm::vec3 tVec = r.Origin - a;

    double u = glm::dot(tVec, pVec) * InvDet;
    if (u < 0 || u > 1)
        return false;

    glm::vec3 qVec = glm::cross(tVec, EdgeV0V1);
    double v = glm::dot(r.Direction, qVec) * InvDet;
    if (v < 0 || u + v > 1)
        return false;

    double t = glm::dot(EdgeV0V2, qVec) * InvDet;

    if (t < t_min || t > t_max)
        return false;

    Rec.t = t;
    Rec.Point = r.At(Rec.t);
    Rec.u = u;
    Rec.v = v;
    // TODO: Use vertex normals if provided
    Rec.Normal = glm::cross(EdgeV0V1, EdgeV0V2);
    Rec.MaterialPtr = MaterialPtr;

    return true;
}