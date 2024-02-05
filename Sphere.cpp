#include "Sphere.h"

Sphere::Sphere(Vector3 center, double radius, std::string material, Color materialColor, double modifier) : center(center), radius(radius), material(material), materialColor(materialColor), modifier(1) {};

Sphere::Sphere(double x, double y, double z, double radius, std::string material, Color materialColor, double modifier) : center(Vector3(x,y,z)), radius(radius), material(material), materialColor(materialColor), modifier(modifier) {};

bool Sphere::isColideWith(Ray ray) {
    Vector3 originCenter = ray.origin - center;

    // Racunamo kvadratnu formulu
    double a = ray.direction.dot(ray.direction);
    double b = 2 * originCenter.dot(ray.direction);
    double c = originCenter.dot(originCenter) - radius * radius;

    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
        return false;
    return true;
};

double Sphere::colision(Ray ray) {
    Vector3 originCenter = ray.origin - center;

    // Racunamo kvadratnu formulu
    double a = ray.direction.dot(ray.direction);
    double b = 2 * originCenter.dot(ray.direction);
    double c = originCenter.dot(originCenter) - radius * radius;

    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
        return -1;
    else
        return (-b - sqrt(discriminant)) / (2.0 * a);
};