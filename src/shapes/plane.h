#ifndef PLANE_H
#define PLANE_H

#include "shape.h"

class Plane : public Shape {
public:
    Plane(const Matrix4x4& obj_to_world)
        : Shape(obj_to_world) { }

    bool intersects(const Ray& r, std::vector<Intersection>& solns) const override;

    Vector normal_at(const Point& p) const override;
    Vector reflect(const Ray& r, const Point& p) const override;


    // Planes lie in xz in object space
    Vector local_normal = Vector(0, 1, 0);
};

std::shared_ptr<Shape> create_plane(const Matrix4x4& obj_to_world);

#endif // PLANE_H