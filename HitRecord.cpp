#include "HitRecord.h"
#include "Util.h"

HitRecord::HitRecord() : point(Vector3()), normal(Vector3()), t(0), isFacingFront(false), modifier(1) {};

bool HitRecord::scatter(Ray ray, HitRecord hr, Color* color, Ray* scatteredRay) {
    if (material == "lambertian") {
        Vector3 scatterDirection = hr.normal + randomUnitVector();

        if (scatterDirection.nearZero())
            scatterDirection = hr.normal;

        *scatteredRay = Ray(hr.point, scatterDirection);
        *color = materialColor;

        return true;
    }
    else if (material == "metal") {
        Vector3 reflected = ray.direction.unitVector().reflect(hr.normal);

        *scatteredRay = Ray(hr.point, reflected + randomUnitVector() * modifier);
        *color = materialColor;

        return true;
    }
    else if (material == "dielectric") {
        double refractionRatio = hr.isFacingFront ? (1.0 / modifier) : modifier;

        Vector3 unitDirection = ray.direction.unitVector();

        double cosineTheta = fmin(-unitDirection.dot(hr.normal), 1);
        double sineTheta = sqrt(1 - cosineTheta * cosineTheta);
        bool cannotRefract = refractionRatio * sineTheta > 1;

        double sa = (1 - refractionRatio) / (1 + refractionRatio);
        sa = sa * sa;
        double reflectance = sa + (1 - sa) * pow((1 - cosineTheta), 5);

        Vector3 direction;

        if (cannotRefract || reflectance > randomDouble())
            direction = unitDirection.reflect(hr.normal);
        else
            direction = unitDirection.refract(hr.normal, refractionRatio);

        *scatteredRay = Ray(hr.point, direction);
        *color = Color(1, 1, 1);

        return true;
    }
    else
        return false;
}