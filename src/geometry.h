#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "double.h"

#include <cassert>
#include <cmath>
#include <iostream>

class Tuple {
public:
    Tuple(double x, double y, double z, int w)
        : x(x), y(y), z(z), w(w) {
    }

    bool is_point() const {
        return w == 1;
    }

    bool is_vector() const {
        return w == 0;
    }

    bool operator==(const Tuple rhs) const {
        return (doubleEqual(x, rhs.x) &&
                doubleEqual(y, rhs.y) &&
                doubleEqual(z, rhs.z) &&
                w == rhs.w);
    }

    Tuple operator+(const Tuple rhs) const {
        return Tuple(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
    }

    Tuple operator-(const Tuple rhs) const {
        return Tuple(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
    }

    Tuple operator-() const {
        return Tuple(-x, -y, -z, -w);
    }

    Tuple operator*(double s) {
        return Tuple(x * s, y * s, z * s, w * s);
    }

    Tuple operator/(double s) {
        return Tuple(x / s, y / s, z / s, w / s);
    }

    // Public Tuple data
    double x, y, z;
    int w;
};

std::ostream &operator<<(std::ostream& os, const Tuple& t) {
    os << (t.is_point() ? "Point( " : "Vector(")
       << t.x << ", "
       << t.y << ", "
       << t.z << ")";
    return os;
}

class Point : public Tuple {
public:
    Point(double x, double y, double z)
        : Tuple(x, y, z, 1) { }
};

class Vector : public Tuple {
public:
    Vector(double x, double y, double z)
        : Tuple(x, y, z, 0) { }


    double magnitudeSquared() const {
        return x*x + y*y + z*z;
    }

    double magnitude() const {
        return std::sqrt(magnitudeSquared());
    }

    Vector normalize() const {
        double len = magnitude();
        return Vector(x / len, y / len, z / len);
    }

    double dot(const Vector rhs) const {
        return (x * rhs.x +
                y * rhs.y +
                z * rhs.z);
    }

    Vector cross(const Vector rhs) const {
        return Vector(y * rhs.z - z * rhs.y,
                      z * rhs.x - x * rhs.z,
                      x * rhs.y - y * rhs.x);
    }
};

#endif // GEOMETRY_H