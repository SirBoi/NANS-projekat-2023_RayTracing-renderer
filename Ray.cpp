#include "Ray.h"

Ray::Ray() : origin(Vector3()), direction(Vector3()), color(Color()) {};

Ray::Ray(Vector3 v1, Vector3 v2) : origin(v1), direction(v2), color(Color()) {};

Ray::Ray(double x1, double y1, double z1, double x2, double y2, double z2) : origin(Vector3(x1, y1, z1)), direction(Vector3(x2, y2, z2)), color(Color()) {};

Vector3 Ray::at(double t) {
	return origin + direction * t;
};
