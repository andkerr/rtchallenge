#ifndef SPHERE_H
#define SPHERE_H

#include "shape.h"

class Sphere : public Shape {
public:
    Sphere(const Point& center, double radius)
        : center(center), radius(radius) { }

    bool intersects(const Ray& r, std::vector<Intersection>& solns) const override;

    // Public Sphere data
    Point center;
    double radius;
};

std::shared_ptr<Shape> create_sphere(const Point& center, double radius);

#endif // SPHERE_H