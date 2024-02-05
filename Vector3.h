#include <iostream>
#pragma once

struct Vector3 {
	double x;
	double y;
	double z;

	Vector3();
	Vector3(double, double);
	Vector3(double, double, double);

	double length();
	double lengthSquared();
	Vector3 unitVector();
	Vector3 randomOnHemisphere();
	Vector3 reflect(Vector3);
	Vector3 refract(Vector3, double);
	Vector3 cross(Vector3);
	double dot(Vector3);
	bool nearZero();

	Vector3 operator+(Vector3);
	Vector3 operator+(double);
	Vector3 operator-(Vector3);
	Vector3 operator-(double);
	Vector3 operator*(double);
	Vector3 operator/(double);
	friend std::ostream& operator<<(std::ostream&, Vector3);
};

Vector3 randomUnitVector();
Vector3 randomInUnitSphere();
Vector3 randomInUnitDisk();
