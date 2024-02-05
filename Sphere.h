#pragma once
#include "Ray.h"
#include "HitRecord.h"

struct Sphere {
	Vector3 center;
	double radius;
	std::string material;
	Color materialColor;
	double modifier;

	Sphere(Vector3, double, std::string, Color, double);
	Sphere(double, double, double, double, std::string, Color, double);

	bool isColideWith(Ray);
	double colision(Ray);
};