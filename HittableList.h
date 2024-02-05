#pragma once
#include "HitRecord.h"
#include "Sphere.h"
#include <vector>

struct HittableList {
    std::vector<Sphere> objects;

    HittableList();

    void clear();
    void add(Sphere);
    bool isHit(Ray, double, double, HitRecord*);
};