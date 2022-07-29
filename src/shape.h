#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include "geometry.h"
#include "material.h"
#include "matrix.h"

#include <exception>
#include <memory> // shared_ptr
#include <vector>

struct Intersection;

class Ray {
public:
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

    Shape(const Matrix4x4& obj_to_world, const Material& material)
        : obj_to_world(obj_to_world), material(material) { }

    virtual bool intersects(const Ray& r, std::vector<Intersection>& solns) const = 0;

    // 7/28: It might make sense to move these elsewhere
    virtual Vector normal(const Point& p) const = 0;
    virtual Vector reflect(const Ray& r, const Point& p) const = 0;

    // Public Shape data
    const Matrix4x4 obj_to_world;

    // It might be advisable to create an additional class at some point
    // for objects that combine a Shape and a Material (a la pbrt's 'Primitive')
    const Material material;
};

struct Intersection {
    Intersection()
        : t(0), obj(nullptr) { }

    Intersection(double t, std::shared_ptr<Shape> obj)
        : t(t), obj(obj) { }

    bool operator==(const Intersection& rhs) const {
        return (t == rhs.t) && (obj == rhs.obj);
    }

    double t;
    std::shared_ptr<Shape> obj;
};

bool find_hit(std::vector<Intersection>& solns, Intersection& hit);

#endif //PRIMITIVES_H