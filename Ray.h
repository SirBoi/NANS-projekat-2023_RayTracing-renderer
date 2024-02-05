#pragma once
#include "Color.h"
#include "Vector3.h"

struct Ray {
	Vector3 origin;
	Vector3 direction;
	Color color;

	Ray();
	Ray(Vector3, Vector3);
	Ray(double, double, double, double, double, double);

	Vector3 at(double);
};