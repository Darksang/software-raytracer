#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include <memory>
#include <vector>

#include "hittable.h"

using std::shared_ptr;
using std::make_shared;

class HittableList : public Hittable {
    public:
        HittableList() { }
        HittableList(shared_ptr<Hittable> Object) { Add(Object); }

        void Clear();
        void Add(shared_ptr<Hittable> Object);

        virtual bool Hit(const Ray & r, double t_min, double t_max, HitRecord & Rec) const override;

    private:
        std::vector<shared_ptr<Hittable>> Objects;
};

#endif