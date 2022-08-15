#include "plane.h"

#include <cassert>
#include <stdexcept>

bool Plane::intersects(const Ray& r, std::vector<Intersection>& solns) const {
    Ray ray = r.transform(obj_to_world.inverse());
    if (doubleEqual(ray.direction.y, 0.)) {
        // local ray is entirely in xz
        return false;
    }
    else {
        // Ray is not parallel to the plane
        double t = -ray.origin.y / ray.direction.y;
        solns.push_back(Intersection(t, std::make_shared<Plane>(*this)));
        return true;
    }
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

std::shared_ptr<Shape> create_plane(const Matrix4x4& obj_to_world) {
    return std::make_shared<Plane>(Plane(obj_to_world));
}