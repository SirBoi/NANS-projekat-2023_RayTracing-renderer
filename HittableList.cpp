#include "HittableList.h"

HittableList::HittableList() {};

void HittableList::clear() {
    objects.clear();
}

void HittableList::add(Sphere sphere) {
    objects.push_back(sphere);
}

bool HittableList::isHit(Ray ray, double min, double max, HitRecord *hr) {
    bool isHitAnything = false;
    double closest = max;
    
    for (Sphere const &sphere : objects) {
        Vector3 originCenter = ray.origin - sphere.center;

        auto a = ray.direction.lengthSquared();
        auto bHalf = originCenter.dot(ray.direction);
        auto c = originCenter.lengthSquared() - sphere.radius * sphere.radius;

        auto discriminant = bHalf * bHalf - a * c;

        if (discriminant < 0)
            continue;

        double root = (-bHalf - sqrt(discriminant)) / a;

        if (root <= min || closest <= root) {
            root = (-bHalf + sqrt(discriminant)) / a;

            if (root <= min || closest <= root)
                continue;
        }

        closest = root;
        hr->t = root;
        hr->point = ray.at(root);
        hr->normal = (hr->point - sphere.center) / sphere.radius;
        hr->material = sphere.material;
        hr->materialColor = sphere.materialColor;
        hr->modifier = sphere.modifier;

        if (ray.direction.dot(hr->normal) >= 0)
            hr->normal = hr->normal * -1;

        isHitAnything = true;
    }
    return isHitAnything;
}