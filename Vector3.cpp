#include "Vector3.h"
#include "Util.h"

Vector3::Vector3() : x(0), y(0), z(0) {};

Vector3::Vector3(double x, double y, double z) : x(x), y(y), z(z) {};

double Vector3::length() {
    return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}

double Vector3::lengthSquared() {
    return this->x * this->x + this->y * this->y + this->z * this->z;
}

Vector3 Vector3::unitVector() {
    return Vector3(this->x / this->length(), this->y / this->length(), this->z / this->length());
};

Vector3 randomInUnitSphere() {
    while (true) {
        Vector3 v = Vector3(randomDouble(), randomDouble(), randomDouble());

        if (v.lengthSquared() < 1)
            return v;
    }
}

Vector3 randomUnitVector() {
    return randomInUnitSphere().unitVector();
}

Vector3 Vector3::randomOnHemisphere() {
    Vector3 v = randomUnitVector();

    if (this->dot(v) > 0)
        return v;
    else
        return v * -1;
}

Vector3 Vector3::reflect(Vector3 v) {
    return *this - v * 2 * this->dot(v);
}

Vector3 Vector3::refract(Vector3 v, double eta) {
    double cosineTheta = fmin(this->dot(v), 1);

    Vector3 perpendicular = (*this + v * cosineTheta) * eta;
    Vector3 parallel = v * -sqrt(fabs(1.0 - perpendicular.lengthSquared()));

    return perpendicular + parallel;
}

Vector3 Vector3::cross(Vector3 v) {
    return Vector3(this->y * v.z - this->z * v.y, this->z * v.x - this->x * v.z, this->x * v.y - this->y * v.x);
}

double Vector3::dot(Vector3 v) {
    return this->x * v.x + this->y * v.y + this->z * v.z;
};

bool Vector3::nearZero() {
    double c = 1e-8;
    return (fabs(x) < c) && (fabs(y) < c) && (fabs(z) < c);
}

Vector3 randomInUnitDisk() {
    while (true) {
        Vector3 v = Vector3(randomDouble(), randomDouble(), 0);

        if (v.lengthSquared() < 1)
            return v;
    }
};

Vector3 Vector3::operator+(Vector3 v) {
	return Vector3(x + v.x, y + v.y, z + v.z);
};
Vector3 Vector3::operator+(double d) {
    return Vector3(x + d, y + d, z + d);
};
Vector3 Vector3::operator-(Vector3 v) {
    return Vector3(x - v.x, y - v.y, z - v.z);
};
Vector3 Vector3::operator-(double d) {
    return Vector3(x - d, y - d, z - d);
};
Vector3 Vector3::operator*(double d) {
    return Vector3(x * d, y * d, z * d);
};
Vector3 Vector3::operator/(double d) {
    return Vector3(x/d, y/d, z/d);
};
std::ostream& operator<<(std::ostream& os, Vector3 v) {
    os << v.x << " " << v.y << " " << v.z << "\n";
    return os;
};
