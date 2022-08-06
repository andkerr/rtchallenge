#ifndef SPHERE_H
#define SPHERE_H

#include "shape.h"

class Sphere : public Shape {
public:
    Sphere(const Matrix4x4& obj_to_world, double radius)
        : Shape(obj_to_world), radius(radius) { }
    
    bool intersects(const Ray& r, std::vector<Intersection>& solns) const override;

    Vector normal_at(const Point& p) const override;
    Vector reflect(const Ray& r, const Point& p) const override;

    // Public Sphere data
    double radius;
};

std::shared_ptr<Shape> create_sphere(const Matrix4x4& obj_to_world,
                                     double radius);

#endif // SPHERE_H