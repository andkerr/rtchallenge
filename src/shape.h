#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include "geometry.h"
#include "material.h"
#include "matrix.h"

#include <exception>
#include <memory>
#include <vector>

struct Intersection;
class Ray;
class Shape;

struct Intersection {
    Intersection()
        : t(0), obj(nullptr) { }

    Intersection(double t, std::shared_ptr<Shape> obj)
        : t(t), obj(obj) { }

    bool operator==(const Intersection& rhs) const {
        return (t == rhs.t) && (obj == rhs.obj);
    }

    bool operator<(const Intersection& rhs) const {
        return t < rhs.t;
    }

    double t;
    std::shared_ptr<Shape> obj;
};

bool find_hit(std::vector<Intersection>& solns, Intersection& hit);


class Ray {
public:
    Ray() = default;

    Ray(const Point& origin, const Vector& direction)
        : origin(origin), direction(direction) { }

    Point displace_by(double t) {
        return origin + direction * t;
    }

    Ray transform(const Matrix4x4& t) const {
        return Ray(t.mul(origin), t.mul(direction));
    }

    bool operator==(const Ray& rhs) const {
        return (origin == rhs.origin) && (direction == rhs.direction);
    }

    // Public Ray data
    Point origin;
    Vector direction;
};


class Shape {
public:
    Shape() = default;

    Shape(const Matrix4x4& obj_to_world)
        : obj_to_world(obj_to_world), material() { }

    virtual ~Shape() = default;

    virtual bool intersects(const Ray& r, std::vector<Intersection>& solns) const = 0;

    virtual Vector normal_at(const Point& p) const = 0;
    virtual Vector reflect(const Ray& r, const Point& p) const = 0;

    Colour pattern_at(const Point& p) const;

    // Public Shape data
    const Matrix4x4 obj_to_world;
    Material material;
};

#endif //PRIMITIVES_H