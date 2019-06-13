#ifndef HITTABLELIST_H
#define HITTABLELIST_H

#include <memory>
#include <vector>
#include "Hittable.h"

class HittableList : public Hittable {

public:

    HittableList() = default;

    HittableList(Hittable **list, int size) : list(list), listSize(size) {}

    virtual bool hit(const Ray &r, float tMin, float tMax, HitRecord &rec) const;

    Hittable **list;
    int listSize;
};

bool HittableList::hit(const Ray &r, float tMin, float tMax, HitRecord &rec) const {

    HitRecord tmpRec;
    bool hitAnything = false;
    double closestAllTime = tMax;

    for (int i = 0; i < listSize; i++) {
        if (list[i]->hit(r, tMin, closestAllTime, tmpRec)) {
            hitAnything = true;
            closestAllTime = tmpRec.t;
            rec = tmpRec;
        }
    }
    return hitAnything;
}

#endif
