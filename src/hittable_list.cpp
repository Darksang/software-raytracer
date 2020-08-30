#include "hittable_list.h"

void HittableList::Clear() {
    Objects.clear();
}

void HittableList::Add(shared_ptr<Hittable> Object) {
    Objects.push_back(Object);
}

bool HittableList::Hit(const Ray & r, double t_min, double t_max, HitRecord & Rec) const {
    HitRecord Result;
    bool HitAnything = false;
    auto ClosestSoFar = t_max;

    for (const auto & Object : Objects) {
        if (Object->Hit(r, t_min, ClosestSoFar, Result)) {
            HitAnything = true;
            ClosestSoFar = Result.t;
            Rec = Result;
        }
    }

    return HitAnything;
}