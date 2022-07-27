#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include "geometry.h"

#include <exception>
#include <memory> // shared_ptr
#include <vector>

struct Intersection;

class Ray {
public:
    Ray(const Point& origin, const Vector& direction)
        : origin(origin), direction(direction) { }

    Point displace(double t) {
        return origin + direction * t;
    }

    // Public Ray data
    Point origin;
    Vector direction;
};

class Shape {
public:
    Shape() { }

    virtual bool intersects(const Ray& r, std::vector<Intersection>& solns) const = 0;
};

struct Intersection {
    Intersection()
        : t(0), obj(nullptr) { }

    Intersection(double t, std::shared_ptr<Shape> obj)
        : t(t), obj(obj) { }

    double t;
    std::shared_ptr<Shape> obj;
};


#endif //PRIMITIVES_H