#pragma once
#include "Vector3.h"
#include "Ray.h"
#include <vector>

struct HitRecord {
    Vector3 point;
    Vector3 normal;
    std::string material;
    Color materialColor;
    double modifier;
    double t;
    bool isFacingFront;

    HitRecord();
    bool scatter(Ray, HitRecord, Color*, Ray*);
};
