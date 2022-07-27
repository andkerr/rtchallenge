#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include "geometry.h"

#include <exception>
#include <memory> // unique_ptr
#include <utility> // pair

class Primitive {
public:
    Primitive() { }

    bool operator==(const Primitive& rhs) {
        return this == &rhs;
    }
};

struct QuadraticCoeffs {
    double a, b, c;
};

struct Intersection {
    Intersection()
        : t1(0), t2(0), obj(nullptr) { }

    Intersection(const Primitive& obj, double t1, double t2)
        : t1(t1), t2(t2), obj(&obj) { }

    double t1, t2;
    const Primitive * obj;
};

class Sphere : public Primitive {
public:
    Sphere(const Point& center, double radius)
        : Primitive(), center(center), radius(radius) { }

    // bool operator==(const Sphere& rhs) const {
    //     return (center == rhs.center) && (radius == rhs.radius);
    // }

    // Public Sphere data
    Point center;
    double radius;
};

class Ray : public Primitive {
public:
    Ray(const Point& origin, const Vector& direction)
        : Primitive(), origin(origin), direction(direction) { }

    Point displace(double t) {
        return origin + direction * t;
    }

    bool intersects(const Sphere& s, Intersection& solns) const; 

    // Public Ray data
    Point origin;
    Vector direction;
};

#endif //PRIMITIVES_H