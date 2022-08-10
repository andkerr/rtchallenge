#include "plane.h"

#include <cassert>
#include <stdexcept>

bool Plane::intersects(const Ray& r, std::vector<Intersection>& solns) const {
    Ray ray = r.transform(obj_to_world.inverse());
    // TODO
}

Vector Plane::normal_at(const Point& p) const {
    Point point = obj_to_world.inverse().mul(p);
    if (!doubleEqual(point.y, 0)) {
        throw std::invalid_argument("Point p does not lie on plane (p.y != in object space)");
    }

    Tuple v_normal_world = obj_to_world.inverse().transpose().mul(local_normal);
    v_normal_world.w = 0;
    
    return Vector(v_normal_world).normalize();
}

Vector Plane::reflect(const Ray& r, const Point& p) const {
    assert(false);
}